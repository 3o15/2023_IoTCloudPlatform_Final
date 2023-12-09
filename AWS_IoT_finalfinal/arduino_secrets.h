// Fill in  your WiFi networks SSID and password
#define SECRET_SSID "gaeun"
#define SECRET_PASS "@12345678"

// Fill in the hostname of your AWS IoT broker
#define SECRET_BROKER "axrwu9gust7g9-ats.iot.ap-northeast-2.amazonaws.com"

// Fill in the boards public certificate
const char SECRET_CERTIFICATE[] = R"(
-----BEGIN CERTIFICATE-----
MIICiDCCAXCgAwIBAgIUEzSjdGpinSBugbRKOPWNTolG+WowDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMTIwNDA3MTgy
MFoXDTQ5MTIzMTIzNTk1OVowGDEWMBQGA1UEAxMNTXlNS1JXaUZpMTAxMDBZMBMG
ByqGSM49AgEGCCqGSM49AwEHA0IABBk4H+2+N5Nri9ozeydR0uoonR7Rwm72jb2Y
nqgy9qDDcxaSsevnhXIUWUlMefuaorEYvR7GsG4eos61FMgbaSujYDBeMB8GA1Ud
IwQYMBaAFG4aGesc3yQAs1aXYFSl1FNPG5wGMB0GA1UdDgQWBBSrBlT4nNZ3Hb9I
RBxOPfx4H+Tg0zAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG
9w0BAQsFAAOCAQEAbBIr27A8sTE5Qf615EhRXzs/SDEfywHJWba/AmgOliVFo8T7
2chFxWGjXnELgjIp4vy6moVuOiK+tLyWrNU6cFE0KwyEQVFBOURxz3T9du5NDaHZ
Sng20bhVuLk/qM036phNIYot6XVNcBf1A79S4Yxkvd/LH1mL2hA/7JlQw38g2QJF
FBtBDu7yeiLB1b9nkkm5x2ZdGSkE9wWfmKE7oBcRQRRDqXVI1YIOCi3xmCl3w9yS
wNNl71/QnwA5ZXM5uh+KTCadFeaywO3AE50ACC/zSkXYMJPA7OArNXfyoPpPgCbC
MoSCoi+3S0K7JLQaOnqK7JaymweP/FsSFe3bDg==
-----END CERTIFICATE-----
)";
