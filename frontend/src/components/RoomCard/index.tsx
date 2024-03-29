import * as React from 'react';
import { Avatar } from 'antd';
import './style.css';
// import { AlignCenterOutlined } from '@ant-design/icons';
import { RoomGame } from 'interfaces/gameInterfaces/interfaces';

interface RoomCardProps {
  room: RoomGame;
  getInRoom: (room: RoomGame) => void;
}

function getRandomColor() {
  const letters = '0123456789ABCDEF';
  let color = '#';
  for (let i = 0; i < 6; i++) {
    color += letters[Math.floor(Math.random() * 16)];
  }
  return color;
}

const RoomCard: React.FC<RoomCardProps> = ({ room, getInRoom }) => (
  <div
    key={Object.keys(room)[0]}
    className="room-card"
    style={{
      display: 'flex',
      flexDirection: 'column',
      alignItems: 'center',
      justifyContent: 'center',
    }}
  >
    <a href="#" onClick={() => getInRoom(room)}>
      <Avatar
        src={room.player1.avatar}
        style={{ backgroundColor: getRandomColor() }}
      >
        {room.player2?.name ? 'X' : 'Livre'}
      </Avatar>
    </a>
    <div
      className="room-info"
      style={{
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
      }}
    >
      <p className="room-name">{room.player1.name}</p>
      <p className="room-name">{room.player2?.name ? 'X' : ''}</p>
      <p className="room-name">{room.player2?.name}</p>
    </div>
  </div>
);

export default RoomCard;
