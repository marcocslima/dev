import { Server } from 'socket.io';
export declare const initialMatch: Match;
export interface Player {
    id: string;
    name: string;
    avatar: null | string;
}
export declare class GameService {
    findRoomByPlayerId(playerId: string, game: Game): string | null;
    removeRoomAndNotify(roomId: string, player: string, game: Game, server: Server): void;
}
export interface Room {
    player1: Player;
    player2: Player;
    match: Match;
    padles: MatchPadle;
}
export interface Game {
    players: {
        [key: string]: Player;
    };
    rooms: {
        [key: string]: Room;
    };
}
export interface Match {
    matchStatus: string;
    ball: {
        x: number;
        y: number;
        width: number;
        xdirection: number;
        ydirection: number;
        xspeed: number;
        yspeed: number;
    };
    score1: number;
    score2: number;
    courtDimensions: {
        width: number;
        height: number;
    };
}
export interface FinalMatch {
    player1: string;
    score1: number;
    player2: string;
    score2: number;
}
export interface MatchPadle {
    player1: {
        y: number;
        playerSpeed: number;
    };
    player2: {
        y: number;
        playerSpeed: number;
    };
}
export interface Padle {
    type: string;
    key: string;
    player: string;
}
