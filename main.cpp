// Online C++ compiler to run C++ program online
#include <iostream>
#include <cstring>
#include <memory>

#define ABSOLUTE_VALUE      0xFFFFFF
#define FIRST               0x1F
#define SECOND              0xFFFFFF90

struct IPAddress_Data
{
    unsigned char       network_id1[4]  = { 0 };
    unsigned char       network_id2[4]  = { 0 };
    
    unsigned char       network_host1[4] = { 0 };
    unsigned char       network_host2[4] = { 0 };
};

std::unique_ptr<struct IPAddress_Data> obtain_network_id(const char *ip_address, std::unique_ptr<struct IPAddress_Data> ip_data)
{
    unsigned int dot, last_dot = 0;
    
    /* Obtain first half of the network ID. */
    while(ip_address[dot] != '.')
        dot++;
        
    memcpy((void *)&ip_data->network_id1, (const void *)ip_address, dot);
    
    /* Obtain second half of the network ID. */
    last_dot = dot++;
    while(ip_address[dot] != '.')
        dot++;
    
    memcpy((void *)&ip_data->network_id2, (const void *)(ip_address + last_dot + 1), dot - last_dot - 1);
    
    return ip_data;
}

std::unique_ptr<struct IPAddress_Data> obtain_host(const char *ip_address, std::unique_ptr<struct IPAddress_Data> ip_data)
{
    unsigned int dot = 0;
    unsigned int last_dot = 0;
    
    /* Skip the first half of the network ID. */
    while(ip_address[dot] != '.')
        dot++;
    
    /* Skip the second half of the network ID. */
    last_dot = dot++;
    while(ip_address[dot] != '.')
        dot++;
        
    /* Obtain the first half of the network host. */
    last_dot = dot++;
    while(ip_address[dot] != '.')
        dot++;
    
    memcpy((void *)ip_data->network_host1, (const void *)(ip_address + last_dot + 1), dot - last_dot - 1);
    
    /* Obtain the second half of the network host. */
    last_dot = dot++;
    while(ip_address[dot] != '\0')
        dot++;
    
    memcpy((void *)ip_data->network_host2, (const void *)(ip_address + last_dot + 1), dot - last_dot - 1);
    
    return ip_data;
}

int main() {
    const char *ip_address = "127.0.0.1";
    
    std::unique_ptr<struct IPAddress_Data> ip_data = std::unique_ptr<struct IPAddress_Data>{new struct IPAddress_Data};
    
    ip_data = obtain_network_id(ip_address, std::move(ip_data));
    ip_data = obtain_host(ip_address, std::move(ip_data));
    
    std::cout << ip_data->network_id1 << ":" 
        << ip_data->network_id2 << ":"
        << ip_data->network_host1 << ":"
        << ip_data->network_host2 << std::endl;
    
    /* Testing. */
    unsigned int a = 0xFFFFFF;
    a <<= 8;
    a |= 0x90;
    int a2 = -0x90;
    printf("%X\n", a2);
    
    printf("%X", a);

    return 0;
}
