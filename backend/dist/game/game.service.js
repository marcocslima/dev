"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.GameService = exports.initialMatch = void 0;
const common_1 = require("@nestjs/common");
exports.initialMatch = {
    matchStatus: 'WAITING',
    ball: {
        x: 580 / 2,
        y: 320 / 2,
        width: 5,
        xdirection: 1,
        ydirection: 1,
        xspeed: 2.8,
        yspeed: 2.2,
    },
    score1: 0,
    score2: 0,
    courtDimensions: { width: 580, height: 320 },
};
let GameService = class GameService {
    findRoomByPlayerId(playerId, game) {
        for (const roomId in game.rooms) {
            const room = game.rooms[roomId];
            if (room.player1.id === playerId || (room.player2 && room.player2.id === playerId)) {
                return roomId;
            }
        }
        return null;
    }
    removeRoomAndNotify(roomId, player, game, server) {
        if (game.rooms[roomId]) {
            const room = game.rooms[roomId];
            game.rooms[roomId].match = exports.initialMatch;
            delete game.rooms[roomId];
        }
    }
};
exports.GameService = GameService;
exports.GameService = GameService = __decorate([
    (0, common_1.Injectable)()
], GameService);
//# sourceMappingURL=game.service.js.map