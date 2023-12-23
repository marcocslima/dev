"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.comparePass = exports.hashPassword = void 0;
const bcrypt = require("bcrypt");
async function hashPassword(password) {
    const salt = 15;
    const hashPass = await bcrypt.hash(password, salt);
    return hashPass;
}
exports.hashPassword = hashPassword;
async function comparePass(inputPassword, hashedPassword) {
    try {
        const pass = await bcrypt.compare(inputPassword, hashedPassword);
        return pass;
    }
    catch (error) {
        throw error;
    }
}
exports.comparePass = comparePass;
//# sourceMappingURL=hash.util.js.map