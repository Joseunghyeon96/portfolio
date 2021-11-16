
# 추가, 수정이 있는 코드들과 이미지만 커밋되어있습니다.   
## 수정내용   
### Texture.h   

Editor에서 사용 될 변수들 추가   
1. bUseSubMipGensettings
2. SubMipStartLevel
3. SubMipGenSettings
![texture_h](https://user-images.githubusercontent.com/49854426/142062445-a5b83cc2-0c81-4309-bc3a-d6d77f942084.png)   

### TextureCompressorModule.h   

FTextureBuildSettings 구조체에 SubMipGenSetting에 사용될 변수들 추가   
1.SubMupSharpening
2.SubSharpnMipKernelsize   
etc...   
![TC_h_1](https://user-images.githubusercontent.com/49854426/142063265-5cec20f1-9031-4914-af80-75e4ee772876.png)

사용할 MipSetting을 바꾸는 SwitchSubMipSetting 함수 추가   
-Sub로 추가되는 변수들을 기존에 있는 변수와 Swap한다.   
![TC_h_2](https://user-images.githubusercontent.com/49854426/142063291-c8670a16-ec19-479b-b690-0744c7911b6e.png)

### TextureCompressorModule.cpp   

BuildTexureMips 함수에서 SubMipSetting을 사용해야한다면 BuildSetting을 바꿔주고   
MipImage에 효과적용시 바꿔서 적용하는 코드를 추가   
   
해당 부분에서 Submip을 사용해야한다면 미리 SubKenelSimpleAverage,SubAddressMode등 변수를 셋팅해준다.   
![TC_cpp_1](https://user-images.githubusercontent.com/49854426/142064006-c57df9d1-87c7-4330-9b6a-da3897519cc6.png)

MipChainDepth를 기반으로 for문이 돌아갈 때 SubMip을 사용해야하는 레벨부터 미리 생성해둔 Sub변수들로 바꿔준 후 밉이미지에 적용한다.   
![TC_cpp_2](https://user-images.githubusercontent.com/49854426/142064146-4f6646db-15ff-41ed-8820-3323baadef26.png)   

### TextureLodSettings.h & cpp

SubMipGenSettings에 맞는 값들을 설정하기 GetMipGenSettings함수에 인자에 TextureMipGenSettings자료형 변수를 추가하였다.   
![TLOD_h](https://user-images.githubusercontent.com/49854426/142064882-446037ce-0e58-4825-9c42-6f7395c90317.png)   

#GetMipGenSettings함수 내부   
기존에는 입력된 Texture에서 MipGenSetting을 기반으로 값들을 셋팅해줬지만 함수 수정으로 인자로 들어온 Setting을 기반으로 OutParam들의 값을 설정한다.   
![TLOD_cpp](https://user-images.githubusercontent.com/49854426/142064895-4e910552-2ab5-4526-8825-979b625dbda4.png)

### TextureDerivedData.cpp

OutParam으로 들어오는 FTextureBuildSettings& OutSettings 변수에 SubMipGenSettings에 맞는 값들을 셋팅해주기 위해 FinalizeBuildSettingsForLayer 함수를 수정하였다.   

이 때 OutSettings에 셋팅되는 SubMipGenSetting에서 파생되는 값들은 미리 FTextureBuildSettings 구조체에 선언해둔 Sub값들에 셋팅해준다.   
![TDD_cpp_1](https://user-images.githubusercontent.com/49854426/142065500-122fa702-2276-4b25-be21-4e385dbc9092.png)   
   
![TDD_cpp_2](https://user-images.githubusercontent.com/49854426/142065504-7d57b6fa-8165-4806-a48e-219393dca3f0.png)   
   
## 결과 창
#### 1024x1024이미지 사이즈를 기반으로 나온 결과입니다. (모든 테스트에서 Sub가 사용되는 MipLevel은 2부터(256x256 size) 사용되게끔 설정했습니다.)
### MipGenSettings = Sharppen0 SubMipGenSettings = Blur5 
설정 값 이미지   
![main-s0_sub-b5](https://user-images.githubusercontent.com/49854426/142066138-4ed8520a-384e-496c-abec-f0dc7b4663e0.png)   
MipLevel1   
![main-s0_sub-b5_miplevel1](https://user-images.githubusercontent.com/49854426/142066148-378e6506-b316-4007-a264-85918636d519.png)   
MipLevel2   
![main-s0_sub-b5_miplevel2](https://user-images.githubusercontent.com/49854426/142066152-94a48bf5-7eef-4c21-83f4-2d91f250ca65.png)   
MipLevel3   
![main-s0_sub-b5_miplevel3](https://user-images.githubusercontent.com/49854426/142066156-0ac195b4-bcc1-4886-82a4-d104689b5f86.png)   
### MipGenSettings = Blur3 SubMipGenSettings = Shappen4
설정 값 이미지   
![main-b3_sub-s4](https://user-images.githubusercontent.com/49854426/142066343-16a5d768-ceec-4d23-822d-7d1943151709.png)   
MipLevel1   
![main-b3_sub-s4_miplevel1](https://user-images.githubusercontent.com/49854426/142066257-e1e461af-dee8-4c4c-8da5-f18a9e2475c0.png)   
MipLevel2   
![main-b3_sub-s4_miplevel2](https://user-images.githubusercontent.com/49854426/142066260-9456e811-5372-4dec-9cbe-64db863f025c.png)   

## 확인 된 버그
#### 한 텍스쳐에서 MipGenSetting 1개마다 BuildTexture함수가 1번만 실행되는 것으로 확인
1. 만약 MipGenSetting을 바꾸지 않고 SubMipGenSetting을 바꾸면 SubSetting이 적용이 되지않습니다.   
2. 이미 특정 MipGenSetting을 설정한 경우, 즉 MipGen = Sharppen 0 ,Sub = Blur5로 한번 설정한 적 있다면,   
   SubMipGenSetting을 바꾸더라도,(MipGen = Sharppen 0, Sub = Blur3등) 새롭게 적용이 되지 않습니다.   
   하지만 사용하지 않은 MipGenSetting의 경우 ( shappen1~blur5) SubMipgenSetting을 바꾸고 설정해준다면 적용이 됩니다.
