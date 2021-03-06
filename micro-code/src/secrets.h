#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "esp32"                         //change this
 
const char WIFI_SSID[] = "Extensor1";               //change this
const char WIFI_PASSWORD[] = "julian123";           //change this
const char AWS_IOT_ENDPOINT[] = "ahz0lyl6465o5-ats.iot.us-east-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUFMNtVGPb6cCaYfHMteQaF0H5j8swDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIyMDUyMDIwMTc0
NVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKzLDD7J9A5pQs/TulA4
0qisQy5YPUF+DNELyYKJDXiQFvQTUk19FFfRa9VneAYhTcMAgM0JDYU6VOpQ5U5J
AdAtNliioAYIro/ffxhX3wVe5s0M6BvJTnPm22Q9jHrWS/pvOi4mLtsxmwPmUVej
im9k9lw8k+pGtXUzWUo80KIslHr0+Pqemix1LJpIVEIWjJOMs5C6zEcWHgv0UNGy
boVpYaan2fYztxNbG7azL+zJH79pSuh+A8UbH8X8qb4cEVu//zEISIXjMBM8TyAK
k6c8YgNWg3ycj838YfMc9FgKSnCT3LU93BXtlB1hbzuUwkYuhfOSkJO2e7n4d6BN
QqMCAwEAAaNgMF4wHwYDVR0jBBgwFoAUmHvu1HY7v883LINRBizRUe+rxcAwHQYD
VR0OBBYEFJxYHRURlGV+oI1emax/K5sevZGdMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQA6nlbvaVfV0FJnZbSXL5ONCREd
2hh2lP1EXP38IZGvj9iUxKjiWveqOx4v58qBasXbQYO67gZnHqXvuGw7H1lK68Ay
oupOaw3nQOolOgX3HRBL9yCx23oCaXbYaUPKeY3rhvIcYolkqR0weL/XCsegRQL6
BfpIWTbrxyliSDl5IdwJT2g9NRCAU4rmW7/kwRdwtCl8GRGRWFUp/rUSjNmWCTY4
EyZF0iww7fnhdCo5f/FEfP1Pmttp+5CMMpeimnW/xfpzh2oPmNDbwCSwBykMvBCu
jU8P+9msIGva//QqhwQqOMLo2JtQUIRDHx33XJo3gbmxBWfj5cdtmdxIKw2F
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEArMsMPsn0DmlCz9O6UDjSqKxDLlg9QX4M0QvJgokNeJAW9BNS
TX0UV9Fr1Wd4BiFNwwCAzQkNhTpU6lDlTkkB0C02WKKgBgiuj99/GFffBV7mzQzo
G8lOc+bbZD2MetZL+m86LiYu2zGbA+ZRV6OKb2T2XDyT6ka1dTNZSjzQoiyUevT4
+p6aLHUsmkhUQhaMk4yzkLrMRxYeC/RQ0bJuhWlhpqfZ9jO3E1sbtrMv7Mkfv2lK
6H4DxRsfxfypvhwRW7//MQhIheMwEzxPIAqTpzxiA1aDfJyPzfxh8xz0WApKcJPc
tT3cFe2UHWFvO5TCRi6F85KQk7Z7ufh3oE1CowIDAQABAoIBADqVAIrNF1RHdaJW
SyVljm4nMQOmYOYyYRACqgf6hTmpyE5puo6Q6HO5iZCparTRV7bUFdbtycqwcxeZ
45Q+BkJZAcLdJ9nD2cLnaASNzgvZF/DO/mZlQpbi3uDGSTlgLBQ034nD4kDoOYEB
9fP7ezS3CxtMYm2cGWspxIz5v1YrrkCrjArrYo8+3SyhPBcf8W0HrEYq0ByxN6EN
vG14R3DofsiaD+ep5crEhRqwn5DghilD0bWB1WPMZGFXgyT7wJi5MFAP85jM1uZY
WteoDgUCvJQ+WIOHMBFdq97irwdHX/Y4PMEQm5c9vfKZX86XXJLVm7A7VP8ZTrcg
rT4j2qECgYEA3Zso2y+bVeaR3tLeXvOmipBSHDh7Wf3SdnA+t8rUtkxm0l62/5uK
Khl0jDYFrzKDAZgucMx0ZhrIuExOMnOaaS5YJRkPlIO8oC0HfYDjI8h6gKMQQRoh
n9tkbhtEC7Ubdax1UxKc8Fy2mhpt3BM6+4Ik8tWQCMkNxCXNBq/7+lMCgYEAx5x0
meBD67jBC4kCAFzxY88RsoDNmPtOCycAjV1RCoIgk8MHU21Rc2PxRvW03Lviyf1o
DUMRFUapdbsOhDxWBIeTpTfBucWoJljbBEs7PCYLc3KyzsoKWijXMTZyAnrhA4x6
laYdkPIsjxA+Z0WgFGtpHiySss7/zM7nFC4MrHECgYBdDWz/dKMWU+YGmab0Wf0h
i+5emTz6kcFRKFq9lDbzgWtfhJP1CtveR6gPxBNo+J3YCo3doYxy32ZPNQNU3gQF
jIdItJg9NX/8Bkxx37AA84q0/0OxAocB9/7Y2SweemLYa50sT9GEgHnQha6BzbVj
rMdVDGYZukrEhVbtKvJ0rwKBgFEoZagirLrslWCxReUL5QFlsZZYFD+8/ZA/PVQ8
urSBD+nEA/iBm/pEilcFk5GjuqPRqjqqKAn0fvXlJhPRzE9vKDKmptd3a9SbkAEA
7YaZGVLJMbYuI2Ng842Iy3YCq/YbacPqlF7YeBF600R95IYo3cZs7QBSdWK6RO3J
g1GhAoGBAKakxKE/Vm+KE3pqJ60/q9y9p5DRq3XQSK25hA5uScWFlEv1fGmU3HZI
zQZjW4bdpxvpBPdHDedZtj99BT1JDJyKTr5F0DD8xHEDSvX2wllqeqDS6Qe+YTIC
rheGUYsNLnXsBRCivUSImMluEdtWVhXcHhSo9AnQ22+4xKOoFU8p
-----END RSA PRIVATE KEY-----
 
 
)KEY";