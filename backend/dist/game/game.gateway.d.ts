import { OnGatewayConnection, OnGatewayDisconnect } from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { GameService, Player, Room } from './game.service';
import { PlayingGameService } from './game.service';
interface Padle {
    type: string;
    key: string;
    player: string;
}
export declare class GamePong implements OnGatewayConnection, OnGatewayDisconnect {
    private readonly gameService;
    private readonly playingGameService;
    server: Server;
    constructor(gameService: GameService, playingGameService: PlayingGameService);
    handleConnection(client: Socket, ...args: any[]): void;
    handleDisconnect(client: Socket): void;
    handleCreateRoom(user: Player, client: Socket): void;
    handleGetInRoom(room: Room, client: Socket): void;
    handleStartMatch(user: Player, client: Socket): Promise<void>;
    handleSendKey(padle: Padle, client: Socket): Promise<void>;
    handleLeaveRoom(user: Player, client: Socket): void;
    handlePlayerConnected(player: any, client: Socket): void;
}
export {};
