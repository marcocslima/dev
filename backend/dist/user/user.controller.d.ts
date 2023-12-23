import { UserService } from './user.service';
export declare class UserController {
    private readonly userService;
    constructor(userService: UserService);
    findAll(): Promise<import("./entities/user.entity").User[]>;
    find(req: any): Promise<{
        id: string;
        name: string;
        email: string;
        username: string;
        avatar: string;
        twoFactorAuth: boolean;
        twoFactorSecret: string;
        createdAt: Date;
        updatedAt: Date;
    }>;
}
