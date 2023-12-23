"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.PlayingGameService = exports.GameService = exports.initialMatch = void 0;
const common_1 = require("@nestjs/common");
exports.initialMatch = {
    room_id: '',
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
            if (player === room.player1.id) {
                server.to(room.room_id).emit('playerLeftRoom', { message: `${room.player1.name} saiu da sala.` });
            }
            else if (room.player2 && player === room.player2.id) {
                server.to(room.room_id).emit('playerLeftRoom', { message: `${room.player2.name} saiu da sala.` });
            }
            delete game.rooms[roomId];
        }
    }
};
exports.GameService = GameService;
exports.GameService = GameService = __decorate([
    (0, common_1.Injectable)()
], GameService);
let PlayingGameService = class PlayingGameService {
    async playGame(match, matchPadle, updateCallback) {
        const playGameRecursive = async () => {
            const xpos = match.ball.x + match.ball.xspeed * match.ball.xdirection;
            const ypos = match.ball.y + match.ball.yspeed * match.ball.ydirection;
            match.ball.x = xpos;
            match.ball.y = ypos;
            const updatedMatchWithColision = await this.handleColision(match, matchPadle);
            if (xpos > match.courtDimensions.width - match.ball.width || xpos < match.ball.width) {
                match.ball.xdirection *= -1;
            }
            if (ypos > match.courtDimensions.height - match.ball.width || ypos < match.ball.width) {
                match.ball.ydirection *= -1;
            }
            if (xpos < match.ball.width) {
                match.score2++;
                match.ball.x = match.courtDimensions.width / 2;
                match.ball.y = match.courtDimensions.height / 2;
            }
            if (xpos > match.courtDimensions.width - match.ball.width) {
                match.score1++;
                match.ball.x = match.courtDimensions.width / 2;
                match.ball.y = match.courtDimensions.height / 2;
            }
            updateCallback(updatedMatchWithColision);
            if (match.matchStatus === 'PLAYING') {
                updateCallback({ ...match });
                await new Promise((resolve) => setTimeout(resolve, 1000 / 60));
                await playGameRecursive();
            }
        };
        await playGameRecursive();
    }
    async latencyGame(roomId, player, game, server) {
        const room = game.rooms[roomId];
        const startTime = new Date().getTime();
        const getLatency = async () => {
            const currentTime = new Date().getTime();
            const latency = currentTime - startTime;
            server.to(room.room_id).emit('ping', latency);
            console.log(latency, '-->', player);
            await new Promise((resolve) => setTimeout(resolve, 5000));
            await getLatency();
        };
        await getLatency();
    }
    async movePadle(padle, matchPadle, player, matchStatus) {
        const updatedPadle = { ...matchPadle };
        if (padle.key === 'ArrowUp') {
            if (player === '1') {
                updatedPadle.player1.y -= 5 * matchPadle.player1.playerSpeed;
            }
            else {
                updatedPadle.player2.y -= 5 * matchPadle.player1.playerSpeed;
            }
        }
        else if (padle.key === 'ArrowDown') {
            if (player === '1') {
                updatedPadle.player1.y += 5 * matchPadle.player1.playerSpeed;
            }
            else {
                updatedPadle.player2.y += 5 * matchPadle.player1.playerSpeed;
            }
        }
        if (player === '1' && updatedPadle.player1.y < 5)
            updatedPadle.player1.y = 2;
        if (player === '2' && updatedPadle.player2.y < 5)
            updatedPadle.player2.y = 2;
        if (player === '1' && updatedPadle.player1.y > matchStatus.courtDimensions.height - 50)
            updatedPadle.player1.y = matchStatus.courtDimensions.height - 50;
        if (player === '2' && updatedPadle.player2.y > matchStatus.courtDimensions.height - 50)
            updatedPadle.player2.y = matchStatus.courtDimensions.height - 50;
        return updatedPadle;
    }
    async handleColision(match, matchPadle) {
        const updatedMatch = { ...match };
        if (updatedMatch.ball.x < 15) {
            if (updatedMatch.ball.y > matchPadle.player1.y - 5 && updatedMatch.ball.y < matchPadle.player1.y + 55) {
                updatedMatch.ball.xdirection *= -1;
            }
        }
        if (updatedMatch.ball.x > updatedMatch.courtDimensions.width - 15) {
            if (updatedMatch.ball.y > matchPadle.player2.y - 5 && updatedMatch.ball.y < matchPadle.player2.y + 55) {
                updatedMatch.ball.xdirection *= -1;
            }
        }
        return updatedMatch;
    }
};
exports.PlayingGameService = PlayingGameService;
exports.PlayingGameService = PlayingGameService = __decorate([
    (0, common_1.Injectable)()
], PlayingGameService);
//# sourceMappingURL=game.service.js.map