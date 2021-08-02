# Attack On Titan

:pushpin: YOUTUBE  : https://youtu.be/v9MUdn2bZEw  

[![TETRIS](https://user-images.githubusercontent.com/49854426/113463625-f189a380-9461-11eb-9a8a-c58051726764.png)](https://youtu.be/v9MUdn2bZEw)

- 메인 캐릭터 움직임(공격/이동) 구현
- 레이 캐스트를 활용한 에임 구현
- 타겟을 판별하여 에임 컬러를 변환했음.
- [백터 계산을 통한 와이어 액션  ](https://github.com/Joseunghyeon96/portfolio/blob/Unity3D_ActionGame/Assets/Script/Character/Player/WireAction.cs)  
플레이어의 현재위치와 와이어의 위치를 벡터로 표현하여 플레이어의 그 벡터의 값만큼 힘을 가하여 최종방향으로 움직이게 하는 움직임. 자연스러운 이동을 위하여 매 프레임마다 이 전에 가해졌던 힘을 없애고 현재 위치와 와이어의 위치의 값을 새로 계산하여 힘을 보내주는 방식으로 구현
