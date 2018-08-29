#pragma once

#include <thread>
#include <libmitcore/Farm.h>

class httpServer
{
public:
	httpServer() {};
    void run(string address, uint16_t port, dev::mit::Farm* farm, bool show_hwmonitors, bool show_power);
    void run_thread();
    void getstat1(stringstream& ss);

    dev::mit::Farm* m_farm;
    std::string m_port;
private:
    void tableHeader(stringstream& ss, unsigned columns);
	bool m_show_hwmonitors;
    bool m_show_power;
};

extern httpServer http_server;

