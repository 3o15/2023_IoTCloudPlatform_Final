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

#### 2. 구조 설명
![image](https://github.com/3o15/2023_IoTCloudPlatform_Final/assets/117139643/50799ad0-dc79-4dd9-86b9-031956e713a4)

1.	IoT 백엔드는 AWS의 AWS IoT Core, AWS Lambda, Amazon DynamoDB, Amazon API Gateway를 이용해 구축된 IoT 클라우드 플랫폼이다.
2.	AWS IoT Device gateway를 통해 연결된 MKRWiFi1010으로부터 주기적으로 사료양(무게 센서 값), 배변패드 상태(유해공기 센서 값) 정보를 수신하고, MQTT 프로토콜을 이용하여 Device shadow, IoT rule 컴포넌트와 상호작용한다.
3.	Device shadow는 Device gateway를 통해 게시된 주제에 따라 디바이스 상태정보를 업데이트하거나 현재 상태정보를 게시한다.
4.	IoT rule은 등록된 주제(update/documents)의 메시지가 수신될 때마다 AWS Lambda 함수를 통해서 수신된 메시지를 Amazon DynamoDB에 저장한다.
5.	Arduino 앱은 Amazon API Gateway를 통해서 게시된 REST API를 활용하여 IoT 백엔드와 상호작용한다.

#### 3. 앱 동작 설명

![깃헙 사진](https://github.com/3o15/2023_IoTCloudPlatform_Final/assets/117643317/3344e0ed-4c03-4aca-95b4-d80f508762c2)

Amazon API Gateway는 AWS Lambda함수를 통해서 다음 기능을 수행하는 두 가지 REST API를 게시한다.
- AWS IoT Core에 등록된 디바이스 목록을 조회하는 REST API
- 디바이스의 정보를 변경하거나 조회하는 REST API
- 디바이스의 로그 정보를 조회하는 REST API

<앱 실행 화면>

![image](https://github.com/3o15/2023_IoTCloudPlatform_Final/assets/117643317/4c41eaec-004e-40e5-bc4b-96d7085551e9)

1. 메인 화면에서 알맞은 Gateway URI를 입력한다.
2. "사물목록 조회" 버튼을 클릭하면 IoTCore에 등록되어 있는 사물의 목록을 확인할 수 있다.
3. 알맞은 사물을 선택한 후, "사물상태 조회/변경" 버튼을 클릭하면 사물의 상태를 조회 및 변경할 수 있는 창이 뜬다.
4. 조회 버튼을 클릭하면 현재 사물이 읽어오는 값을 띄우기 때문에 실시간으로 값이 변하는 것을 확인할 수 있다.
5. 변경하는 곳에 알맞은 문자열(open/close)를 입력한 후 변경 버튼을 누르면 값이 변하는 것을 확인할 수 있다. 앱을 통해 변경한 값이 AWS에 들어가고, AWS는 사물에게 전달하여 변경된 값으로 제어를 진행하게 된다.
6. "로그 조회" 버튼을 클릭하면 DynamoDB에 올라와있는 로그값들을 조회할 수 있는 창이 뜬다.
7. 조회할 로그 시간값을 입력하고 조회 버튼을 클릭하면 밑에 DynamoDB에 올라와있는 해당 시간대의 로그값들이 리스트로 쫙 뜨는 것을 확인할 수 있다. 
