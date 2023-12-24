import { Server } from 'socket.io';
export declare const initialMatch: Match;
export interface Player {
    id: string;
    name: string;
    avatar: null | string;
}
export interface PlayingGameInstance {
    playGame: (match: Match, matchPadle: MatchPadle, updateCallback: (updatedMatch: Match) => void) => Promise<void>;
}
export declare class GameService {
    findRoomByPlayerId(playerId: string, game: Game): string | null;
    removeRoomAndNotify(roomId: string, player: string, game: Game, server: Server): void;
}
export declare class PlayingGameService implements PlayingGameInstance {
    playGame(match: Match, matchPadle: MatchPadle, updateCallback: (updatedMatch: Match) => void): Promise<void>;
    latencyGame(roomId: string, player: string, game: Game, server: Server): Promise<void>;
    movePadle(padle: Padle, matchPadle: MatchPadle, player: string, matchStatus: Match): Promise<MatchPadle>;
    handleColision(match: Match, matchPadle: MatchPadle): Promise<Match>;
}
export interface Room {
    room_id: string;
    player1: Player;
    player2: Player;
    match: Match;
    playingGameInstance?: PlayingGameInstance;
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
    room_id: string;
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
