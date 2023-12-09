# 2023_IoTCloudPlatform_Final
## AWS를 이용한 IoT 클라우드 플랫폼 프로젝트
### 주제 : IoT PetCare Sentinel; IoT 애완동물 케어 서비스

#### 1.주요 기능

1.사료 원격 급여 및 관리             
>_*사용자는 앱의 버튼으로 서보모터를 제어하여 사료 배식_    
_*사료그릇에 있는 무게센서를 통해 사료량 파악, 30g(임의의 값)이 될 때 서보모터가 자동으로 움직여 배식 중단_    

2.암모니아 측정 및 경고 알림             
>_*배변패드 근처에 유해공기질센서와 LED를 위치_     
_*애완동물의 배변에 의해 유해공기질센서 값이 90이상(임의의 값)이면 앱에 알림을 전송함과 동시에 LED ON_      
_*주인이 배변패드를 교체하면 유해공기질센서 값이 감소하여 LED OFF_      

3.급여 및 배변 이력 기록 및 제공                  
>_*사료 그릇의 무게값과 서보모터값으로 배식 횟수와 양을 파악 가능_     
_*유해공기질센서 값의 변화와 LED 동작값으로 배변 상태를 파악 가능_      
_*이 데이터들이 쌓여 추후 애완동물의 건강에 문제가 생겨 병원을 방문할 경우 유용하게 활용 가능_
       
(구조도 사진 첨부란)

