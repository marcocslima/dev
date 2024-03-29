import { Controller } from '@nestjs/common';
import { ApiTags } from '@nestjs/swagger';
import {
  WebSocketGateway,
  WebSocketServer,
  OnGatewayConnection,
  OnGatewayDisconnect,
  SubscribeMessage,
  MessageBody,
  ConnectedSocket,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { GameService, Player, Room, Game, Match, MatchPadle, FinalMatch, initialMatch } from './game.service';
// import { PlayingGameService } from './game.service';

interface Padle {
  type: string;
  key: string;
  player: string;
}

const game: Game = {
  players: {},
  rooms: {},
};

const matchPadle: MatchPadle = {
  player1: { y: 135, playerSpeed: 1.5 },
  player2: { y: 135, playerSpeed: 1.5 },
};

let matchStatus: FinalMatch;

@ApiTags('pong')
@Controller('pong')
@WebSocketGateway({ cors: { origin: 'http://localhost:3000' } })
export class GamePong implements OnGatewayConnection, OnGatewayDisconnect {
  @WebSocketServer()
  server: Server;

  // constructor(private readonly gameService: GameService, private readonly playingGameService: PlayingGameService) { }
  constructor(private readonly gameService: GameService) { }

  handleConnection(client: Socket, ...args: any[]) { }

  handleDisconnect(client: Socket) {
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

  @SubscribeMessage('CreateRoom')
  handleCreateRoom(@MessageBody() user: Player, @ConnectedSocket() client: Socket) {
    const playerAlreadyInRoom = Object.values(game.rooms).find(
      (room) => room.player1.id === user.id || (room.player2 && room.player2.id === user.id),
    );

    if (!playerAlreadyInRoom) {
      client.join(client.id);
      const match: Match = { ...initialMatch };
      game.rooms[client.id] = { player1: { ...user }, player2: null, match: { ...match }, padles: { ...matchPadle } };
    } else {
      console.log('The Player is already in the room:', client.id);
    }
    this.server.emit('game', game);
  }

  @SubscribeMessage('GetInRoom')
  handleGetInRoom(@MessageBody() room: Room, @ConnectedSocket() client: Socket) {
    // const playerAlreadyInRoom = Object.values(game.rooms).find(
    //   (existingRoom) =>
    //     existingRoom.player1.id === room.player2.id || (existingRoom.player2 && existingRoom.player2.id === room.player2.id),
    // );
    console.log(game);

    // if (!playerAlreadyInRoom && game.rooms.player2 === null) {
    //   client.join(room);
    //   game.rooms[room.room_id].player2 = { ...room.player2 };
    // } else {
    //   console.log('The Player is already in the room:', client.id);
    // }
    // this.server.emit('game', game);
  }

  @SubscribeMessage('startMatch')
  async handleStartMatch(@MessageBody() user: Player, @ConnectedSocket() client: Socket) {
    const roomId = this.gameService.findRoomByPlayerId(user.id, game);
    // let startMatch: Match = { ...game.rooms[roomId].match, matchStatus: 'PLAYING', room_id: roomId };
    game.rooms[roomId].match = { ...initialMatch, matchStatus: 'PLAYING' };
    game.rooms[roomId].padles = { ...matchPadle };

    // if (game.rooms[roomId]) {
    //   try {
    //     if (!game.rooms[roomId].playingGameInstance) {
    //       game.rooms[roomId].playingGameInstance = new PlayingGameService();
    //     }
    //     await game.rooms[roomId].playingGameInstance.playGame(game.rooms[roomId].match, game.rooms[roomId].padles, (updatedMatch) => {
    //       this.server.to(game.rooms[roomId].room_id).emit('matchStarted', {
    //         match: { ...updatedMatch }
    //       });
    // console.log(game.rooms[roomId].match);
    // console.log(game.rooms[roomId].room_id, game.rooms[roomId].padles);
    // const date = new Date();
    // console.log(date.toString(), updatedMatch, roomId)
    // matchStatus = {
    //   player1: game.rooms[roomId].player1.id,
    //   score1: updatedMatch.score1,
    //   player2: game.rooms[roomId].player2.id,
    //   score2: updatedMatch.score2,
    // };
    //     });
    //   } catch (error) { }
    // }
  }

  @SubscribeMessage('sendKey')
  async handleSendKey(@MessageBody() padle: Padle, @ConnectedSocket() client: Socket) {
    const roomId = this.gameService.findRoomByPlayerId(padle.player, game);
    const matchRoom: Room = { ...game.rooms[roomId] };
    const player = game.rooms[roomId].player1.id === padle.player ? '1' : '2';
    const direction = padle.type === 'keyup' ? 'STOP' : 'GO';

    // if (game.rooms[roomId] && direction === 'GO') {
    //   await this.playingGameService.movePadle(padle, game.rooms[roomId].padles, player, matchRoom);
    //   // const updatedPadle = await this.playingGameService.movePadle(padle, game.rooms[roomId].padles, player, matchRoom);
    //   // console.log(matchStatus);
    //   this.server.to(game.rooms[roomId].room_id).emit('movePadle', { matchPadle: { ...game.rooms[roomId].padles } });
    // }
  }

  @SubscribeMessage('leaveRoom')
  handleLeaveRoom(@MessageBody() user: Player, @ConnectedSocket() client: Socket) {
    const roomId = this.gameService.findRoomByPlayerId(user.id, game);

    // if (game.rooms[roomId]) {
    //   this.gameService.removeRoomAndNotify(roomId, user.id, game, this.server);
    //   client.leave(roomId);
    //   this.server.emit('game', game);
    //   try {
    //     this.server.to(game.rooms[roomId].room_id).emit('playerLeftRoom', 'GameOver: Player left the room!');
    //   } catch (error) { }
    // } else {
    //   console.error(`Room not found for user ${user.id}`);
    // }
  }

  @SubscribeMessage('PlayerConnected')
  handlePlayerConnected(@MessageBody() player: any, @ConnectedSocket() client: Socket) {
    const existingPlayer = game.players[client.id];

    if (!existingPlayer) {
      game.players[client.id] = { id: player.id, name: player.username, avatar: player.avatar };
    } else {
      console.log('Player with the same ID already exists:', player.id);
    }
    this.server.emit('game', game);
  }
}
