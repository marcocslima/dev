import { BaseEntity } from 'typeorm';
export declare class User extends BaseEntity {
    id: string;
    name: string;
    email: string;
    password: string;
    username: string;
    avatar: string;
    twoFactorAuth: boolean;
    twoFactorSecret: string;
    createdAt: Date;
    updatedAt: Date;
}
