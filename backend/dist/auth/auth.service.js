"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.AuthService = void 0;
const common_1 = require("@nestjs/common");
const jwt_1 = require("@nestjs/jwt");
const axios_1 = require("axios");
const uuid_1 = require("uuid");
const auth_config_1 = require("../configs/auth.config");
const user_service_1 = require("../user/user.service");
const hash_util_1 = require("../utils/hash.util");
const twoFactor_util_1 = require("../utils/twoFactor.util");
const speakeasy = require("speakeasy");
let AuthService = class AuthService {
    constructor(userService, jwtService) {
        this.userService = userService;
        this.jwtService = jwtService;
    }
    async signIn(username, password) {
        const user = await this.userService.findUsername(username);
        if (!user) {
            throw new common_1.UnauthorizedException();
        }
        const matchPass = await (0, hash_util_1.comparePass)(password, user.password);
        if (!matchPass) {
            throw new common_1.UnauthorizedException();
        }
        const payload = { sub: user.id, username: user.username };
        return {
            access_token: await this.jwtService.signAsync(payload),
        };
    }
    async verifyOTP(body) {
        const user = await this.userService.findUser(body.userId);
        const verified = speakeasy.totp.verify({
            secret: user.twoFactorSecret,
            encoding: 'base32',
            token: body.otp,
        });
        return { verified };
    }
    async signUp(name, email, username, password) {
        const hashPass = await (0, hash_util_1.hashPassword)(password);
        password = hashPass;
        username = username.replace(/\s/g, '');
        const userWithLogin = await this.userService.findByUsername(username);
        if (userWithLogin) {
            username = (0, uuid_1.v4)();
        }
        const twoFactorSecret = await (0, twoFactor_util_1.twoFactorGenerator)();
        const user = await this.userService.create({
            name,
            email,
            username,
            password,
            twoFactorSecret,
        });
        const payload = { sub: user.id, username: user.username };
        return {
            access_token: await this.jwtService.signAsync(payload),
        };
    }
    async requestAccessToken(code) {
        try {
            const data = new URLSearchParams();
            data.append('grant_type', 'authorization_code');
            data.append('client_id', auth_config_1.default.clientId);
            data.append('client_secret', auth_config_1.default.clientSecret);
            data.append('code', code);
            data.append('redirect_uri', auth_config_1.default.redirectUri);
            const response = await axios_1.default.post(auth_config_1.default.tokenUrl, data);
            return response.data;
        }
        catch (error) {
            throw error;
        }
    }
    async requestResourceOwner(token) {
        try {
            const response = await axios_1.default.get(auth_config_1.default.getResourceOwnerUrl, {
                headers: {
                    Authorization: `Bearer ${token}`,
                },
            });
            return response.data;
        }
        catch (error) {
            throw error;
        }
    }
    async signInWith42(code) {
        try {
            const token = await this.requestAccessToken(code);
            const resourceOwner = await this.requestResourceOwner(token.access_token);
            if (!resourceOwner.email || !token.access_token) {
                throw new common_1.HttpException('Login using oauth 42 was not allowed', common_1.HttpStatus.FORBIDDEN);
            }
            let user = await this.userService.findEmail(resourceOwner.email);
            if (!user) {
                let username = resourceOwner.login.replace(/\s/g, '');
                const userWithLogin = await this.userService.findByUsername(resourceOwner.login);
                if (userWithLogin) {
                    username = (0, uuid_1.v4)();
                }
                user = await this.userService.createFromOAuth({
                    name: resourceOwner.usual_full_name,
                    email: resourceOwner.email,
                    username,
                    avatar: resourceOwner?.image?.link ?? '',
                });
            }
            const payload = { sub: user.id, username: user.username };
            return {
                access_token: await this.jwtService.signAsync(payload),
            };
        }
        catch (error) {
            const errorMessage = error.response?.status
                ? `Error getting data: ${error.message}`
                : error.request
                    ? 'Unable to get response from server'
                    : 'Error configuring the request';
            const status = error.response?.status || common_1.HttpStatus.INTERNAL_SERVER_ERROR;
            throw new common_1.HttpException(errorMessage, status);
        }
    }
};
exports.AuthService = AuthService;
exports.AuthService = AuthService = __decorate([
    (0, common_1.Injectable)(),
    __metadata("design:paramtypes", [user_service_1.UserService,
        jwt_1.JwtService])
], AuthService);
//# sourceMappingURL=auth.service.js.map