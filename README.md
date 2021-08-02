# TETRIS

[![TETRIS](https://img.youtube.com/vi/2AWB5vQy4sU/hqdefault.jpg)](https://youtu.be/2AWB5vQy4sU)

### 싱글톤 패턴
- 메인화면, UI화면 구현
### 컴포넌트 패턴
- 블록 이동/변환/홀드 
![image](https://user-images.githubusercontent.com/49854426/127808215-e55e05f2-c5f2-4ec1-89c4-d470f499f944.png)

여러 개의 컴포넌트들중 특정한 Object에 필요한 것들을 AddComponent함수를 사용하여 부착 후
싱글톤 패턴으로 구현된 MainGame에서 Update함수를 진행할 때 Object를 업데이트 하면
내부에서 부착된 컴포넌트들을 getComponent() 함수로 불러와 각 컴포넌트들을 업데이트 해주는 방식으로 구현
