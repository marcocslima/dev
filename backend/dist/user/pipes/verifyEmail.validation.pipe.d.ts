import { PipeTransform } from '@nestjs/common';
import { UserService } from '../user.service';
import { CreateUserDto } from '../dto/create-user.dto';
export declare class EmailExistsValidationPipe implements PipeTransform<CreateUserDto> {
    private readonly userService;
    constructor(userService: UserService);
    transform(value: CreateUserDto): Promise<CreateUserDto>;
}
