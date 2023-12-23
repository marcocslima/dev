"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const core_1 = require("@nestjs/core");
const app_module_1 = require("./app.module");
const swagger_1 = require("@nestjs/swagger");
async function bootstrap() {
    const app = await core_1.NestFactory.create(app_module_1.AppModule);
    const config = new swagger_1.DocumentBuilder()
        .setTitle('Documentação com Swagger - Fábrica de Sinapse')
        .setDescription('O Swagger (aka OpenApi) é uma biblioteca muito conhecida no universo backend, estando disponível para diversas linguagens e frameworks. Ela gera um site interno no seu backend que descreve, com muitos detalhes, cada endpoint e estrutura de entidades presentes na sua aplicação.')
        .setVersion('1.0')
        .addTag('auth')
        .addTag('user')
        .addTag('pong')
        .addBearerAuth({
        description: `Please enter token in following format: Bearer <JWT>`,
        name: 'Authorization',
        bearerFormat: 'Bearer',
        scheme: 'Bearer',
        type: 'http',
        in: 'Header',
    }, 'access-token')
        .build();
    const document = swagger_1.SwaggerModule.createDocument(app, config);
    swagger_1.SwaggerModule.setup('api', app, document);
    app.enableCors({
        origin: 'http://localhost:3000',
        credentials: true,
    });
    app.use(function (request, response, next) {
        response.header('Access-Control-Allow-Origin', '*');
        next();
    });
    await app.listen(3003);
}
bootstrap();
//# sourceMappingURL=main.js.map