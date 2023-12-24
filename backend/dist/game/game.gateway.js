"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
var __param = (this && this.__param) || function (paramIndex, decorator) {
    return function (target, key) { decorator(target, key, paramIndex); }
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.GamePong = void 0;
const common_1 = require("@nestjs/common");
const swagger_1 = require("@nestjs/swagger");
const websockets_1 = require("@nestjs/websockets");
const socket_io_1 = require("socket.io");
const game_service_1 = require("./game.service");
const game = {
    players: {},
    rooms: {},
};
const matchPadle = {
    player1: { y: 135, playerSpeed: 1.5 },
    player2: { y: 135, playerSpeed: 1.5 },
};
let matchStatus;
let GamePong = class GamePong {
    constructor(gameService) {
        this.gameService = gameService;
    }
    handleConnection(client, ...args) { }
    handleDisconnect(client) {
        const playerId = game.players[client.id]?.id;
        const roomId = this.gameService.findRoomByPlayerId(playerId, game);
        if (roomId) {
            this.gameService.removeRoomAndNotify(roomId, playerId, game, this.server);
            client.leave(roomId);
        }
        if (playerId) {
            delete game.players[client.id];
        }
        this.server.emit('game', game);
    }
    handleCreateRoom(user, client) {
        const playerAlreadyInRoom = Object.values(game.rooms).find((room) => room.player1.id === user.id || (room.player2 && room.player2.id === user.id));
        if (!playerAlreadyInRoom) {
            client.join(client.id);
            const match = { ...game_service_1.initialMatch };
            game.rooms[client.id] = { player1: { ...user }, player2: null, match: { ...match }, padles: { ...matchPadle } };
        }
        else {
            console.log('The Player is already in the room:', client.id);
        }
        this.server.emit('game', game);
    }
    handleGetInRoom(room, client) {
        console.log(game);
    }
    async handleStartMatch(user, client) {
        const roomId = this.gameService.findRoomByPlayerId(user.id, game);
        game.rooms[roomId].match = { ...game_service_1.initialMatch, matchStatus: 'PLAYING' };
        game.rooms[roomId].padles = { ...matchPadle };
    }
    async handleSendKey(padle, client) {
        const roomId = this.gameService.findRoomByPlayerId(padle.player, game);
        const matchRoom = { ...game.rooms[roomId] };
        const player = game.rooms[roomId].player1.id === padle.player ? '1' : '2';
        const direction = padle.type === 'keyup' ? 'STOP' : 'GO';
    }
    handleLeaveRoom(user, client) {
        const roomId = this.gameService.findRoomByPlayerId(user.id, game);
    }
    handlePlayerConnected(player, client) {
        const existingPlayer = game.players[client.id];
        if (!existingPlayer) {
            game.players[client.id] = { id: player.id, name: player.username, avatar: player.avatar };
        }
        else {
            console.log('Player with the same ID already exists:', player.id);
        }
        this.server.emit('game', game);
    }
};
exports.GamePong = GamePong;
__decorate([
    (0, websockets_1.WebSocketServer)(),
    __metadata("design:type", socket_io_1.Server)
], GamePong.prototype, "server", void 0);
__decorate([
    (0, websockets_1.SubscribeMessage)('CreateRoom'),
    __param(0, (0, websockets_1.MessageBody)()),
    __param(1, (0, websockets_1.ConnectedSocket)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object, socket_io_1.Socket]),
    __metadata("design:returntype", void 0)
], GamePong.prototype, "handleCreateRoom", null);
__decorate([
    (0, websockets_1.SubscribeMessage)('GetInRoom'),
    __param(0, (0, websockets_1.MessageBody)()),
    __param(1, (0, websockets_1.ConnectedSocket)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object, socket_io_1.Socket]),
    __metadata("design:returntype", void 0)
], GamePong.prototype, "handleGetInRoom", null);
__decorate([
    (0, websockets_1.SubscribeMessage)('startMatch'),
    __param(0, (0, websockets_1.MessageBody)()),
    __param(1, (0, websockets_1.ConnectedSocket)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object, socket_io_1.Socket]),
    __metadata("design:returntype", Promise)
], GamePong.prototype, "handleStartMatch", null);
__decorate([
    (0, websockets_1.SubscribeMessage)('sendKey'),
    __param(0, (0, websockets_1.MessageBody)()),
    __param(1, (0, websockets_1.ConnectedSocket)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object, socket_io_1.Socket]),
    __metadata("design:returntype", Promise)
], GamePong.prototype, "handleSendKey", null);
__decorate([
    (0, websockets_1.SubscribeMessage)('leaveRoom'),
    __param(0, (0, websockets_1.MessageBody)()),
    __param(1, (0, websockets_1.ConnectedSocket)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object, socket_io_1.Socket]),
    __metadata("design:returntype", void 0)
], GamePong.prototype, "handleLeaveRoom", null);
__decorate([
    (0, websockets_1.SubscribeMessage)('PlayerConnected'),
    __param(0, (0, websockets_1.MessageBody)()),
    __param(1, (0, websockets_1.ConnectedSocket)()),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", [Object, socket_io_1.Socket]),
    __metadata("design:returntype", void 0)
], GamePong.prototype, "handlePlayerConnected", null);
exports.GamePong = GamePong = __decorate([
    (0, swagger_1.ApiTags)('pong'),
    (0, common_1.Controller)('pong'),
    (0, websockets_1.WebSocketGateway)({ cors: { origin: 'http://localhost:3000' } }),
    __metadata("design:paramtypes", [game_service_1.GameService])
], GamePong);
//# sourceMappingURL=game.gateway.js.map