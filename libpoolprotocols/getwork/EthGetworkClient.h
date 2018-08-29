#pragma once

#include <jsonrpccpp/client/connectors/httpclient.h>
#include <iostream>
#include <libdevcore/Worker.h>
#include "jsonrpc_getwork.h"
#include "../PoolClient.h"

using namespace std;
using namespace dev;
using namespace mit;

class MitGetworkClient : public PoolClient, Worker
{
public:
	MitGetworkClient(unsigned farmRecheckPeriod, bool submitHashrate);
	~MitGetworkClient();

	void connect() override;
	void disconnect() override;

	bool isConnected() override { return m_connected; }
	bool isPendingState() override { return false; }

	string ActiveEndPoint() override { return ""; };

	void submitHashrate(string const & rate) override;
	void submitSolution(const Solution& solution) override;

private:
	void workLoop() override;
	unsigned m_farmRecheckPeriod = 500;

	string m_currentHashrateToSubmit = "";

	h256 m_client_id;
	JsonrpcGetwork *p_client = nullptr;
	WorkPackage m_prevWorkPackage;

	// Hashrate submission is optional
	bool m_submit_hashrate;
};
