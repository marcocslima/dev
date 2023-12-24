import { Module } from '@nestjs/common';
import { GamePong } from './game.gateway';
import { GameService } from './game.service';
// import { PlayingGameService } from './game.service';

@Module({
  // providers: [GamePong, GameService, PlayingGameService],
  providers: [GamePong, GameService],
})

export class GameModule { }
