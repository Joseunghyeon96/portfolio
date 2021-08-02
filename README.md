# DirectX11 론 월드탐험

:pushpin: YOUTUBE : https://youtu.be/tj49JlCKDxk

[![TETRIS](http://img.youtube.com/vi/tj49JlCKDxk/sddefault.jpg)](https://youtu.be/tj49JlCKDxk)
  
  
  
## Character Class  
![image](https://user-images.githubusercontent.com/49854426/127868820-a55f9343-6d2f-4d9c-b971-17961cb4badc.png)  
- Character의 상태 정보를 Enum으로 관리  
- Animation Notify Event를 사용하여 캐릭터의 상태 정보, 콜라이더 on/off, 파티클, 사운드..등 실행  
- Dash 사용시 캐릭터 메쉬 머테리얼 을 변환하여 잔상 효과 연출  

## 전투 시스템  
  - Anim Notify와 NativeEvent를 사용한 콤보 어택 시스템 구현   
  - Delegate Event를 이용한 대시 이펙트  
  - 트레일과 파티클을 이용한 스킬 구현  
  - Enemy    
  ![image](https://user-images.githubusercontent.com/49854426/127869532-c80844db-eff2-485d-b2df-45e1a8eb69b1.png)  
  ```
    - 보스 몬스터는 Behavior Tree를 사용
    - 일반 몬스터는 Detected Collider와 Combat Collider를 통하여 Detect범위에 플레이어가 들어온다면 HP UI를 보여주고 플레이어를 추격
    - Service 노드를 통하여 메인 플레이어(타겟)를 탐색하고 Decorator를 통하여 특정 패턴을 사용하는 조건에 부합하는지 체크한 후 BTTask를 통하여 패턴을 실행
  ```
    
## Item  
![image](https://user-images.githubusercontent.com/49854426/127870379-d8ac9989-ec9d-4a83-a4a0-94c6ddc7e828.png)  
  - [csv파일을 이용한 아이템 데이터 불러오기](https://github.com/Joseunghyeon96/portfolio/blob/UE4_RPG/Source/please/MyGameInstance.h)  
  - [Item Class](https://github.com/Joseunghyeon96/portfolio/blob/UE4_RPG/Source/please/Items/Item.h)의 가상 함수 사용  
  - Potion 클래스에서는 개수를 따로 변수로 두어 중복적인 포션을 습득했을 때 미리 인벤토리에 있는 포션객체의 개수를 올려서 객체의 개수가 지나치게 증가하는 현상 방지  
  - Weapon은 메쉬에 추가로 Socket을 생성하여 전투 시 사용하는 콜라이더를 Socket의 위치로 변환하여 각 무기별로 다른 부분에 위치  
  
## Inventory  
  - 실제 인벤토리에 추가되는 아이템의 정보는 Inventory Component를 통하여 관리  
  - 델리게이트 이벤트 연동을 통하여 인벤토리의 아이템이 업데이트 될 때마다 User Widget의 이미지가 업데이트   
  - 마우스 Drag, Drop, Click의 기능을 지원하며 배열의 각 요소는 Main Player의 Inventory Component가 가지고 있는 내용들을 불러와 사용자에게 보여줌  
  - UI Widget Blueprint와 C++를 이용한 인벤토리와 아이템 툴팁, 퀵 슬롯 기능 구현  
 ```
    - 델리게이트 이벤트를 통한 실시간 인벤토리, 퀵 슬롯 업데이트 구현  
    - DragDropOperation을 이용한 인벤토리와 퀵슬롯 간 드래그 앤 드랍 시스템 구현  
    - 키 바인딩을 통한 퀵 슬롯 아이템 사용 구현  
 ```
  
