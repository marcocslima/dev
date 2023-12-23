export declare function hashPassword(password: string): Promise<string>;
export declare function comparePass(inputPassword: string, hashedPassword: string): Promise<boolean>;
