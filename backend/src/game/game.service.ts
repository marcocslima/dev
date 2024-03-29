import { Injectable } from '@nestjs/common';
import { Server } from 'socket.io';

export const initialMatch: Match = {
  // room_id: '',
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

export interface Player {
  id: string;
  name: string;
  avatar: null | string;
}

// export interface PlayingGameInstance {
//   playGame: (match: Match, matchPadle: MatchPadle, updateCallback: (updatedMatch: Match) => void) => Promise<void>;
// }

@Injectable()
export class GameService {
  findRoomByPlayerId(playerId: string, game: Game): string | null {
    for (const roomId in game.rooms) {
      const room = game.rooms[roomId];

      if (room.player1.id === playerId || (room.player2 && room.player2.id === playerId)) {
        return roomId;
      }
    }
    return null;
  }

  removeRoomAndNotify(roomId: string, player: string, game: Game, server: Server): void {
    if (game.rooms[roomId]) {
      const room = game.rooms[roomId];
      game.rooms[roomId].match = initialMatch;
      // if (player === room.player1.id) {
      //   server.to(room.room_id).emit('playerLeftRoom', { message: `${room.player1.name} saiu da sala.` });
      // } else if (room.player2 && player === room.player2.id) {
      //   server.to(room.room_id).emit('playerLeftRoom', { message: `${room.player2.name} saiu da sala.` });
      // }
      delete game.rooms[roomId];
    }
  }
}

// @Injectable()
// export class PlayingGameService implements PlayingGameInstance {
// async playGame(match: Match, updateCallback: (updatedMatch: Match) => void): Promise<void> {
//   const playGameRecursive = async () => {
//     const xpos = match.ball.x + match.ball.xspeed * match.ball.xdirection;
//     const ypos = match.ball.y + match.ball.yspeed * match.ball.ydirection;

//     match.ball.x = xpos;
//     match.ball.y = ypos;

//     if (xpos > match.courtDimensions.width - match.ball.width || xpos < match.ball.width) {
//       match.ball.xdirection *= -1;
//     }

//     if (ypos > match.courtDimensions.height - match.ball.width || ypos < match.ball.width) {
//       match.ball.ydirection *= -1;
//     }

//     if (match.matchStatus === 'PLAYING') {
//       updateCallback({ ...match });
//       await new Promise((resolve) => setTimeout(resolve, 3000));
//       await playGameRecursive();
//     }
//   };
//   await playGameRecursive();
// }

// async latencyGame(roomId: string, player: string, game: Game, server: Server): Promise<void> {
//   const room = game.rooms[roomId];
//   const startTime = new Date().getTime();

//   const getLatency = async () => {
//     const currentTime = new Date().getTime();
//     const latency = currentTime - startTime;
//     // server.to(room.room_id).emit('ping', latency);

//     console.log(latency, '-->', player);

//     await new Promise((resolve) => setTimeout(resolve, 5000));
//     await getLatency();
//   };

//   await getLatency();
// }

// async movePadle(padle: Padle, matchPadle: MatchPadle, player: string, matchRoom: Room): Promise<void> {
//   // const updatedPadle: MatchPadle = { ...matchPadle };

//   if (padle.key === 'ArrowUp') {
//     if (player === '1') {
//       matchRoom.padles.player1.y -= 5 * matchPadle.player1.playerSpeed;
//     } else {
//       matchRoom.padles.player2.y -= 5 * matchPadle.player2.playerSpeed;
//     }
//   } else if (padle.key === 'ArrowDown') {
//     if (player === '1') {
//       matchRoom.padles.player1.y += 5 * matchPadle.player1.playerSpeed;
//     } else {
//       matchRoom.padles.player2.y += 5 * matchPadle.player2.playerSpeed;
//     }
//   }

//   if (player === '1' && matchRoom.padles.player1.y < 5) matchRoom.padles.player1.y = 2;
//   if (player === '2' && matchRoom.padles.player2.y < 5) matchRoom.padles.player2.y = 2;
//   if (player === '1' && matchRoom.padles.player1.y > 270)
//     matchRoom.padles.player1.y = 270;
//   if (player === '2' && matchRoom.padles.player2.y > 270)
//     matchRoom.padles.player2.y = 270;

// return updatedPadle;
//   }

//   async handleColision(match: Match, matchPadle: MatchPadle): Promise<Match> {
//     const updatedMatch: Match = { ...match };

//     if (updatedMatch.ball.x < 15) {
//       if (updatedMatch.ball.y > matchPadle.player1.y - 5 && updatedMatch.ball.y < matchPadle.player1.y + 55) {
//         updatedMatch.ball.xdirection *= -1;
//       }
//     }

//     if (updatedMatch.ball.x > updatedMatch.courtDimensions.width - 15) {
//       if (updatedMatch.ball.y > matchPadle.player2.y - 5 && updatedMatch.ball.y < matchPadle.player2.y + 55) {
//         updatedMatch.ball.xdirection *= -1;
//       }
//     }
//     return updatedMatch;
//   }
// }

export interface Room {
  player1: Player;
  player2: Player;
  match: Match;
  padles: MatchPadle;
  // playingGameInstance?: PlayingGameInstance;
}

export interface Game {
  players: { [key: string]: Player };
  rooms: { [key: string]: Room };
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
  courtDimensions: { width: number; height: number };
}

export interface FinalMatch {
  player1: string;
  score1: number;
  player2: string;
  score2: number;
}

export interface MatchPadle {
  player1: { y: number; playerSpeed: number };
  player2: { y: number; playerSpeed: number };
}

export interface Padle {
  type: string;
  key: string;
  player: string;
}
