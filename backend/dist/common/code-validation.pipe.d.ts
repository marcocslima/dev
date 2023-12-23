import { ArgumentMetadata, PipeTransform } from '@nestjs/common';
export declare class ParamExistValidationPipe implements PipeTransform {
    transform(value: any, metadata: ArgumentMetadata): any;
}
