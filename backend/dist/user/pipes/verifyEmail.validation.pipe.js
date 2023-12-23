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
exports.EmailExistsValidationPipe = void 0;
const common_1 = require("@nestjs/common");
const user_service_1 = require("../user.service");
let EmailExistsValidationPipe = class EmailExistsValidationPipe {
    constructor(userService) {
        this.userService = userService;
    }
    async transform(value) {
        const emailExists = await this.userService.findEmail(value.email);
        if (emailExists) {
            throw new common_1.BadRequestException('Email is already in use.');
        }
        return value;
    }
};
exports.EmailExistsValidationPipe = EmailExistsValidationPipe;
exports.EmailExistsValidationPipe = EmailExistsValidationPipe = __decorate([
    (0, common_1.Injectable)(),
    __metadata("design:paramtypes", [user_service_1.UserService])
], EmailExistsValidationPipe);
//# sourceMappingURL=verifyEmail.validation.pipe.js.map