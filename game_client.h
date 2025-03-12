#ifdef __cplusplus
extern "C"
{
#endif
    void error(const char *msg);
    void initSocket(const char *serv_addr_str);
    void closeClient();
    void sendPosition(int x, int y);
    void handleSocketSetup(const char *serv_addr_str, const char *portno_str);
#ifdef __cplusplus
}
#endif