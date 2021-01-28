/******************************************************************************
* File Name:   tcp_server.h
*
* Description: This file contains declaration of task and functions related to
* TCP server operation.
*
*******************************************************************************
* (c) 2020, Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* ("Software"), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries ("Cypress") and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software ("EULA").
*
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress's integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Cypress against all liability.
*******************************************************************************/

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

/*******************************************************************************
* Macros
********************************************************************************/
/* Wi-Fi Credentials: Modify WIFI_SSID, WIFI_PASSWORD, and WIFI_SECURITY_TYPE
 * to match your Wi-Fi network credentials.
 * Note: Maximum length of the Wi-Fi SSID and password is set to
 * CY_WCM_MAX_SSID_LEN and CY_WCM_MAX_PASSPHRASE_LEN as defined in cy_wcm.h file.
 */
#define WIFI_SSID                                 "ssid"
#define WIFI_PASSWORD                             "pswd"

/* Security type of the Wi-Fi access point. See 'cy_wcm_security_t' structure
 * in "cy_wcm.h" for more details.
 */
#define WIFI_SECURITY_TYPE                        CY_WCM_SECURITY_WPA2_AES_PSK

/* Maximum number of connection retries to a Wi-Fi network. */
#define MAX_WIFI_CONN_RETRIES                     (10u)

/* Wi-Fi re-connection time interval in milliseconds */
#define WIFI_CONN_RETRY_INTERVAL_MSEC             (1000)

/* TCP server related macros. */
#define TCP_SERVER_PORT                           (40508)
#define TCP_SERVER_MAX_PENDING_CONNECTIONS        (3)
#define TCP_SERVER_RECV_TIMEOUT_MS                (4000)
#define MAX_TCP_RECV_BUFFER_SIZE                  (20)
#define MAX_TCP_DATA_PACKET_LENGTH				  (20)

/* TCP server certificate. Copy from the TCP server certificate
 * generated by OpenSSL (See Readme.md on how to generate a SSL certificate).
 */
#define keySERVER_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDhTCCAm0CFHpvc/v8K67YWp7SkKZ+U8UgDBvRMA0GCSqGSIb3DQEBCwUAMH8x\n"\
"CzAJBgNVBAYTAklOMRIwEAYDVQQIDAlLYXJuYXRha2ExGDAWBgNVBAcMD0Jlbmdh\n"\
"bHVydRtbQxtbRDEQMA4GA1UECgwHQ3lwcmVzczEUMBIGA1UECwwLRW5naW5lZXJp\n"\
"bmcxGjAYBgNVBAMMEW15dGNwc2VjdXJlc2VydmVyMB4XDTE5MTIwNTA1MjUwMloX\n"\
"DTIwMTIwNDA1MjUwMlowfzELMAkGA1UEBhMCSU4xEjAQBgNVBAgMCUthcm5hdGFr\n"\
"YTEYMBYGA1UEBwwPQmVuZ2FsdXJ1G1tDG1tEMRAwDgYDVQQKDAdDeXByZXNzMRQw\n"\
"EgYDVQQLDAtFbmdpbmVlcmluZzEaMBgGA1UEAwwRbXl0Y3BzZWN1cmVzZXJ2ZXIw\n"\
"ggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDbYpG/jopHvy6j2ln5Dbxg\n"\
"XaQRwu/kHAE9WuxA6svYPWcZ5txqXvP1hPjVPsU74lxc/ckZlgSGspMc/ubc/BFS\n"\
"LoZ6Br5IjzpGx0nxA2g7Rb2EzSKhVoZDqc356S3lBFnf6quKfAlqKSAbv3uvjTbt\n"\
"up0Fnb0rZnMIBrZHQf5m/KMmDmlYHkEPVRXlx3UvNx2v2+22ktdD86R7AOPjjopo\n"\
"M9963Z24pQ6QRA7MrDiAFG7ajKrPwJpbJ5DgzD72+LSIPjejKeFiP5S3LgUvPXv8\n"\
"neQ3UdXCY/8M44yULhKRlhKIk+B5vwBWfm8IxAfJCsktREomUM0jGoJScljVJmul\n"\
"AgMBAAEwDQYJKoZIhvcNAQELBQADggEBAAqyZAIRhNJumQnLM0Kke8lobUpBS0Cq\n"\
"kSaC1zQIQ8w6ruVAXVMohE9DFQbBk7OgX8HxUzDUQIL6h9i2knF0dNseKSFvul4w\n"\
"4I6eYopg/jsTmEkWOgcw9bXb7ibJDjmxSOx9nPXy7ouyqw1/jMlEqAZ8l8hWMYA+\n"\
"fsdkah64dvGTLfhyXpOtF/TUjhLG4A3y6VMTJcZhWbqmIBaY45u9c6nRksM/5ZX9\n"\
"B6PWtpHE5Q4GfQJavgnlLhaOOTuznhssBKIMzTFivAA35RYL5btRsQkKu/2oALP4\n"\
"yg+tikuvKL2cuAHvFmHbAlJcn5wsTMBLb5AU6pacdtS0uPvsD5QHEgM=\n"\
"-----END CERTIFICATE-----\n"

/* Private key of the TCP Server. Copy from the TCP server key
 * generated by OpenSSL (See Readme.md on how to create a private key).
 */
#define keySERVER_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpQIBAAKCAQEA22KRv46KR78uo9pZ+Q28YF2kEcLv5BwBPVrsQOrL2D1nGebc\n"\
"al7z9YT41T7FO+JcXP3JGZYEhrKTHP7m3PwRUi6Gega+SI86RsdJ8QNoO0W9hM0i\n"\
"oVaGQ6nN+ekt5QRZ3+qrinwJaikgG797r4027bqdBZ29K2ZzCAa2R0H+ZvyjJg5p\n"\
"WB5BD1UV5cd1Lzcdr9vttpLXQ/OkewDj446KaDPfet2duKUOkEQOzKw4gBRu2oyq\n"\
"z8CaWyeQ4Mw+9vi0iD43oynhYj+Uty4FLz17/J3kN1HVwmP/DOOMlC4SkZYSiJPg\n"\
"eb8AVn5vCMQHyQrJLURKJlDNIxqCUnJY1SZrpQIDAQABAoIBAQCMJJ5oWNz60iUw\n"\
"JIb/MwgYIxlxAy8Nb9pW4GM1YQgQvcDD6hb5mGiNeYEfb/a8t3A7Mx+oyY1gomiZ\n"\
"yDegCSHjdrcO8onRfjVDC4GvhXarDnTvhb9OgyBHzww2Tf+0YaAsCxPD5lJ5T4Yk\n"\
"U6DmVvY0zNYLxWUXeV2YTflY8c5a6G86j55IEDEUGQRsAfzhgSZr/WMGxXEBmaC4\n"\
"JvCO8bR03c+4f5rgo+i8Nuv6FT1g+N3uMUlODtVQV3gDOMaLTgOa0UYMicuJ8yKB\n"\
"r37KQvnkZzaEmVEOItcxhrP2/Gn4MnomaaK+6y19eN8mp1qBEPSrUS7iiQQ9Z+ci\n"\
"KlyXiVBBAoGBAPTysRSQHD6USr6HoU+mLyTjqWdvF44naLOtM4rmYa+ffWrc+6sI\n"\
"Z7cwmQiM4ltPvax4iX3qmvDijcjDYmk8MlgHxlcPT6ulg2zb2ArMuJlo/UWQgNtI\n"\
"MOFUdXA9UUN7oARLuJeCwq1MMTvVLZVfp/sNLqpnVTNOi8qc/TXBgrpRAoGBAOVI\n"\
"m9BqBOBv72bpY4Qw2RuXLSGPUpYSwtpv3gMxDWc9WLd8wAhSSRw0irS+ZWS8glQZ\n"\
"s9TjMIN/HUlTERjT7AeV2MANt4/9Dz34JjMSRldLoUlnsXuUDEdE1bZbZcCSR8K8\n"\
"4RlsmZc/dlTBv+99PoukfbwlMzFZQYOHrz+SnzMVAoGBAMqUQMGp4cIbsKlc0Jtn\n"\
"7IuMwZjqtsd5bk1TTFJu8JFnzTjpJDayT9ygk6APrFEqZMrUMZnywkvAgtRsSuKP\n"\
"x28olu9/mTtzOnt4YnekEnPF8dlrhjZUwSBKUooOHDw8bP3AhhzAJzNd1UYPq5Bj\n"\
"OTEXGOYTadJx/okGRyADN5PRAoGAZ2OGX0RvToUq/szfAwzD2Z0hzLBEHUf4dWdc\n"\
"RTQpRxRynMq0DQyNyxomMbppHjOi0SmF3clUZvc6zYWXgAqPtBvt0SxeSZ9i8B6l\n"\
"mwHylgqUf/UyIvdvUfPIKqKsD1nm4fkpx70gxQLo6O81DVj8ixtxVxWvL+F/mT/l\n"\
"1lTXVMECgYEAtI5QCTG57euaGUQyQr4YAmBkiNTblkXehEUPbTfHCuSJOBM4i/Es\n"\
"cTa8zcgojGXLyRWWsZRGej+CelRsJO/IiO1xnujOx/kqLllcJO1EDFXrKdfAZkMs\n"\
"ek4Nx8CUDDxeU8hEnrb2uHGnw/w5PoLIrT9RASa2AzdMr900XlnMg48=\n"\
"-----END RSA PRIVATE KEY-----\n"

/* TCP client certificate. In this example this is the RootCA
 * certificate so as to verify the TCP client's identity. */
#define keyCLIENT_ROOTCA_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIEHTCCAwWgAwIBAgIUXbJ1O2vQBqwoLQfeDsclV92K3OEwDQYJKoZIhvcNAQEL\n"\
"BQAwgZ0xCzAJBgNVBAYTAklOMRIwEAYDVQQIDAlLYXJuYXRha2ExEjAQBgNVBAcM\n"\
"CUJlbmdhbHVydTEPMA0GA1UECgwGTXlfb3JnMRUwEwYDVQQLDAxNeV91bml0X25h\n"\
"bWUxHTAbBgNVBAMMFG15X3RjcF9zZWN1cmVfY2xpZW50MR8wHQYJKoZIhvcNAQkB\n"\
"FhBteV9lbWFpbF9hZGRyZXNzMB4XDTIwMDQyMjA0MDQzMVoXDTIxMDQyMjA0MDQz\n"\
"MVowgZ0xCzAJBgNVBAYTAklOMRIwEAYDVQQIDAlLYXJuYXRha2ExEjAQBgNVBAcM\n"\
"CUJlbmdhbHVydTEPMA0GA1UECgwGTXlfb3JnMRUwEwYDVQQLDAxNeV91bml0X25h\n"\
"bWUxHTAbBgNVBAMMFG15X3RjcF9zZWN1cmVfY2xpZW50MR8wHQYJKoZIhvcNAQkB\n"\
"FhBteV9lbWFpbF9hZGRyZXNzMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC\n"\
"AQEA7IHHX47X3e6k2EQhAVRtoWAu1ZDM3QcoIJgBTogChgyZeBpFfqOPtbprXqta\n"\
"O0WunvKnjxeDYl+o8M2ypeXNTjSdkBskQMQSXhvXwUdo/inERO5uAkZGRRxJdhyf\n"\
"aiHqBTxlDSS1EhbTrEnIhO4nNBLa47mfwy+b3gLgL79QUTQOZghDykOv77J5rSHE\n"\
"TWlGoOoYi7OBHBenft3GjZHNpRj8NxfYb8JhoS95xMvhAdvE43XJGpaI7nbrlxHM\n"\
"ubkzHEbhpm8QPq+Rs9yxSUju0TUq2NGGsYLA8Fe+XlB4s1rD5eazcgIlIm7xR+OK\n"\
"d7kwCOTWItO9tmA0vO+AmAraCwIDAQABo1MwUTAdBgNVHQ4EFgQUSpHfzaRQqDDV\n"\
"ujoKaO6CyIEY9OcwHwYDVR0jBBgwFoAUSpHfzaRQqDDVujoKaO6CyIEY9OcwDwYD\n"\
"VR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAwGuni6FtWoUDdCYDUyHc\n"\
"YVIWIZxXt1eHDfaHRngHZ5O3xFUnAh7iiFCieUPr9zZvvdWfbLB/k6YMhmvPviEF\n"\
"ODBnIbOL2wYv5q1a4U0koQAy/7zCsCAgS71klFupdeLiyHf13s8HkmxOPRjHuout\n"\
"DElcCJY0f9su9MtsCRiF87j9xqBi9JThw7lFK6AuTa9sOhB23gHafTgxOQ5SXeRk\n"\
"GULhFsbp9p7IQ7+z+igMFOqUkbWCf914PmqG37mYq/Z039l6rXGcjoV6PH4dySH6\n"\
"CPH38iG5aeYCepi7+Q7JG/tu7DJdXwGtXuWYKto8d2/JqZVMAB80XM1kFXDUn45X\n"\
"Nw==\n"\
"-----END CERTIFICATE-----\n"

/*******************************************************************************
* Function Prototypes
********************************************************************************/
void tcp_server_task(void *arg);

#endif /* TCP_SERVER_H_ */
