import { Repository } from 'typeorm';
import { CreateUserDto } from './dto/create-user.dto';
import { User } from './entities/user.entity';
import { CreateFromOAuthDto } from './dto/create-from-oauth.dto';
export declare class UserService {
    private usersRepository;
    constructor(usersRepository: Repository<User>);
    create(createUserDto: CreateUserDto): Promise<User>;
    createFromOAuth(createUserOAuthDto: CreateFromOAuthDto): Promise<User>;
    findUser(id: string): Promise<{
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
    findAll(): Promise<User[]>;
    findById(id: string): Promise<User>;
    findByUsername(username: string): Promise<User>;
    findUsername(username: string): Promise<User>;
    findEmail(email: string): Promise<User>;
}
