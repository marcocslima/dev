"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ParamExistValidationPipe = void 0;
const common_1 = require("@nestjs/common");
class ParamExistValidationPipe {
    transform(value, metadata) {
        if (!value) {
            throw new common_1.BadRequestException(`${metadata.data} parameter is mandatory`);
        }
        return value;
    }
}
exports.ParamExistValidationPipe = ParamExistValidationPipe;
//# sourceMappingURL=code-validation.pipe.js.map