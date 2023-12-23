"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.twoFactorGenerator = void 0;
const speakeasy = require("speakeasy");
async function twoFactorGenerator() {
    const secret = speakeasy.generateSecret({ length: 20 });
    return Promise.resolve(secret.base32);
}
exports.twoFactorGenerator = twoFactorGenerator;
//# sourceMappingURL=twoFactor.util.js.map