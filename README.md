# DirectX11 론 월드탐험

:pushpin: YOUTUBE : https://www.youtube.com/watch?v=A4W7M9-fP-I

<img src="https://user-images.githubusercontent.com/49854426/113464364-f00eaa00-9466-11eb-844f-5dd59c2a94cb.png" width="100%" height="100%">

- 내적, 삼각함수를 사용한 카메라 움직임
- 스카이 돔, 스카이 플레인과 구름모양 스프라이트의 이동을 이용하여 하늘 구현  
하늘을 표현하는 스카이 돔의 윗 부분(반구)을 3분할하여 각 지점의 색상을 정한 후 각각의 값들로 선형보간법을 사용하여 하늘의 색을 표현하고, 하루의 하늘의 색을 3가지(낮, 노을, 밤) 설정한 후 특정한 시간에  가까워질수록 다음 하늘의 색의 값이 되도록 구현  
- 조명의 방향의 변화를 이용한 시간의 흐름
- Vertex shader , Pixel Shader를 이용한 direction, point light 감쇄 효과 연산  
참고: https://blog.nullbus.net/58  
맵에 생성되어 있는 점 조명들의 위치를 가져와서 오브젝트와의 일정한 거리(임의적으로 정한 가장 강한 세기의 빛이 올 수 있는 최대거리) 보다 멀다면 계산하지 않고 가깝다면 빛의 강도와 색상을 곱하여 각 조명들을 더해 픽셀의 값을 계산 후 텍스처 색상과 Direction Light를 통한 연산을 끝낸 값과 곱하여 최종색상을 반환해주는 방식으로 구현
