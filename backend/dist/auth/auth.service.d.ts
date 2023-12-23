import { JwtService } from '@nestjs/jwt';
import { UserService } from 'src/user/user.service';
export declare class AuthService {
    private readonly userService;
    private jwtService;
    constructor(userService: UserService, jwtService: JwtService);
    signIn(username: any, password: any): Promise<{
        access_token: string;
    }>;
    verifyOTP(body: {
        userId: string;
        otp: string;
    }): Promise<{
        verified: boolean;
    }>;
    signUp(name: any, email: any, username: any, password: any): Promise<{
        access_token: string;
    }>;
    requestAccessToken(code: string): Promise<any>;
    requestResourceOwner(token: string): Promise<any>;
    signInWith42(code: string): Promise<{
        access_token: string;
    }>;
}
