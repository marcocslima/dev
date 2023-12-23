import { AuthService } from './auth.service';
import { LoginDto } from 'src/user/dto/login.dto';
import { CreateUserDto } from 'src/user/dto/create-user.dto';
import { UserService } from 'src/user/user.service';
export declare class AuthController {
    private readonly authService;
    private readonly userService;
    constructor(authService: AuthService, userService: UserService);
    handleToken(code: string): Promise<{
        access_token: string;
    }>;
    signIn(loginDto: LoginDto): Promise<{
        access_token: string;
    }>;
    signUp(createUserDto: CreateUserDto): Promise<{
        access_token: string;
    }>;
    verifyOTP(body: {
        userId: string;
        otp: string;
    }): Promise<{
        verified: boolean;
    }>;
    getProfile(req: any): any;
}
