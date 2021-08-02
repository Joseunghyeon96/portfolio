# DirectX11 론 월드탐험

:pushpin: YOUTUBE : https://youtu.be/tj49JlCKDxk

[![TETRIS](http://img.youtube.com/vi/tj49JlCKDxk/sddefault.jpg)](https://youtu.be/tj49JlCKDxk)

#### UI Widget Blueprint와 C++를 이용한 인벤토리와 아이템 툴팁, 퀵 슬롯 기능 구현  
  - 델리게이트 이벤트를 통한 실시간 인벤토리, 퀵 슬롯 업데이트 구현  
  - DragDropOperation을 이용한 인벤토리와 퀵슬롯 간 드래그 앤 드랍 시스템 구현  
  - 키 바인딩을 통한 퀵 슬롯 아이템 사용 구현

#### Inventory Component를 통한 아이템 관리  
  - 실제 인벤토리에 추가되는 아이템의 정보는 Inventory Component를 통하여 관리  
  - 델리게이트 이벤트 연동을 통하여 인벤토리의 아이템이 업데이트 될 때마다 User Widget의 이미지가 업데이트  

#### csv파일을 이용한 아이템 데이터 불러오기  
  - UGameInstance와 FTableRowBase를 사용하여 import된 csv파일의 정보를 아이템에 연동  

#### 전투 시스템  
  - 애니메이션 노티파이와 NativeEvent를 사용한 콤보 어택 시스템 구현  
  - Delegate Event를 이용한 대시 이펙트  
  - 트레일과 파티클을 이용한 스킬 구현  
  - 비헤이비어 트리를 이용한 보스몬스터 구현  
