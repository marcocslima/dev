export interface Player {
  id: string;
  name: string;
  avatar: string | null;
}

export interface RoomGame {
  player1: Player;
  player2: Player;
  match: Match;
  padles: MatchPadle;
}

export interface GameData {
  players: { [key: string]: Player };
  rooms: { [key: string]: RoomGame };
  status: string;
  match: boolean;
  connected: boolean;
  message: string;
}

export interface Match {
  room_id: string;
  matchStatus: string;
  ball: {
    x: number;
    y: number;
    width: number;
  };
  score1: number;
  score2: number;
  courtDimensions: { width: number; height: number };
}

export interface MatchPadle {
  player1: { y: number; playerSpeed: number };
  player2: { y: number; playerSpeed: number };
}

export const initialMatch: Match = {
  room_id: '',
  matchStatus: 'WAITING',
  ball: {
    x: 580 / 2,
    y: 320 / 2,
    width: 5,
  },
  score1: 0,
  score2: 0,
  courtDimensions: { width: 580, height: 320 },
};

export const initialMatchPadle: MatchPadle = {
  player1: { y: 135, playerSpeed: 1.5 },
} as MatchPadle;
