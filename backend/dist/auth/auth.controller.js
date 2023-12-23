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
var __param = (this && this.__param) || function (paramIndex, decorator) {
    return function (target, key) { decorator(target, key, paramIndex); }
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.AuthController = void 0;
const common_1 = require("@nestjs/common");
const auth_service_1 = require("./auth.service");
const swagger_1 = require("@nestjs/swagger");
const code_validation_pipe_1 = require("../common/code-validation.pipe");
const login_dto_1 = require("../user/dto/login.dto");
const create_user_dto_1 = require("../user/dto/create-user.dto");
const verifyEmail_validation_pipe_1 = require("../user/pipes/verifyEmail.validation.pipe");
const user_service_1 = require("../user/user.service");
const constants_1 = require("../common/constants");
let AuthController = class AuthController {
    constructor(authService, userService) {
        this.authService = authService;
        this.userService = userService;
    }
    async handleToken(code) {
        return await this.authService.signInWith42(code);
    }
    async signIn(loginDto) {
        return await this.authService.signIn(loginDto.username, loginDto.password);
    }
    async signUp(createUserDto) {
        await new verifyEmail_validation_pipe_1.EmailExistsValidationPipe(this.userService).transform(createUserDto);
        return await this.authService.signUp(createUserDto.name, createUserDto.email, createUserDto.username, createUserDto.password);
    }
    async verifyOTP(body) {
        return await this.authService.verifyOTP(body);
    }
    getProfile(req) {
        return req.user;
    }
};
exports.AuthController = AuthController;
__decorate([
    (0, swagger_1.ApiOperation)({ description: 'Request 42 access token' }),
    (0, swagger_1.ApiQuery)({ name: 'code', type: String, required: true }),
    (0, constants_1.Public)(),
    (0, common_1.HttpCode)(common_1.HttpStatus.OK),
    (0, common_1.Post)('42'),
    __param(0, (0, common_1.Query)('code', code_validation_pipe_1.ParamExistValidationPipe)),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [String]),
    __metadata("design:returntype", Promise)
], AuthController.prototype, "handleToken", null);
__decorate([
    (0, swagger_1.ApiOperation)({ description: 'Login user' }),
    (0, swagger_1.ApiBody)({ type: login_dto_1.LoginDto, description: 'Login request body.' }),
    (0, constants_1.Public)(),
    (0, common_1.HttpCode)(common_1.HttpStatus.OK),
    (0, common_1.Post)('login'),
    __param(0, (0, common_1.Body)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [login_dto_1.LoginDto]),
    __metadata("design:returntype", Promise)
], AuthController.prototype, "signIn", null);
__decorate([
    (0, swagger_1.ApiOperation)({ description: 'Create a new user' }),
    (0, swagger_1.ApiBody)({ type: create_user_dto_1.CreateUserDto, description: 'Request body.' }),
    (0, constants_1.Public)(),
    (0, common_1.HttpCode)(common_1.HttpStatus.CREATED),
    (0, common_1.Post)('sign-up'),
    __param(0, (0, common_1.Body)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [create_user_dto_1.CreateUserDto]),
    __metadata("design:returntype", Promise)
], AuthController.prototype, "signUp", null);
__decorate([
    (0, swagger_1.ApiOperation)({ description: 'Verify 2FT' }),
    (0, swagger_1.ApiBody)({ type: create_user_dto_1.CreateUserDto, description: 'Request body.' }),
    (0, constants_1.Public)(),
    (0, common_1.HttpCode)(common_1.HttpStatus.OK),
    (0, common_1.Post)('two-factor-auth'),
    __param(0, (0, common_1.Body)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object]),
    __metadata("design:returntype", Promise)
], AuthController.prototype, "verifyOTP", null);
__decorate([
    (0, swagger_1.ApiOperation)({ description: 'Get req user' }),
    (0, swagger_1.ApiBearerAuth)('access-token'),
    (0, common_1.Get)('profile'),
    __param(0, (0, common_1.Request)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object]),
    __metadata("design:returntype", void 0)
], AuthController.prototype, "getProfile", null);
exports.AuthController = AuthController = __decorate([
    (0, swagger_1.ApiTags)('auth'),
    (0, common_1.Controller)('auth'),
    __metadata("design:paramtypes", [auth_service_1.AuthService,
        user_service_1.UserService])
], AuthController);
//# sourceMappingURL=auth.controller.js.map