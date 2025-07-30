#include "pch.h"
#include <unordered_set>
#include <random>

using namespace std;

struct VNode {
	int server;
	uint32_t  hash;
};

std::random_device rd; // Obtain a random number from hardware
std::mt19937 gen(rd()); // Seed the engine
std::uniform_int<uint32_t> dist(0, std::numeric_limits<uint32_t>::max());
static uint32_t getRandomHash() {
	return dist(gen);
}

class ConsistentHashing {
	// Higher number - more even distribution, but longer look-up
	// lower number - faster look-up, but less even distribution
	const int NUM_OF_VNODES = 100;
	unordered_set<int> servers;
	vector<VNode> vnodes;
	
	uint32_t newVNode() {
		return getRandomHash();
	}
public:
	ConsistentHashing(int numServers) {
		for (int i = 0; i < numServers; i++) {
			servers.insert(i);
			for (int j=0; j<NUM_OF_VNODES; j++) vnodes.push_back({ i, newVNode() });
		}
		std::sort(vnodes.begin(), vnodes.end(), [](const VNode& a, const VNode& b) { return a.hash < b.hash; });
	}

	bool addServer(int serverNum) {
		if (servers.contains(serverNum)) return false;
		servers.insert(serverNum);
		for (int j = 0; j < NUM_OF_VNODES; j++) vnodes.push_back({ serverNum, newVNode() });
		std::sort(vnodes.begin(), vnodes.end(), [](const VNode& a, const VNode& b) { return a.hash < b.hash; });
		return true;
	}

	bool removeServer(int serverNum) {
		if (!servers.contains(serverNum)) return false;
		servers.erase(serverNum);
		int read, write;
		for (read = 0, write = 0; read < vnodes.size(); read++) {
			if (vnodes[read].server != serverNum) {
				vnodes[write] = vnodes[read];
				write++;
			}
		}
		vnodes.resize(write);
	}

	int getServer(uint32_t  hash) {
		if (hash <= vnodes.front().hash || vnodes.back().hash < hash) return vnodes.front().server;
		auto it = std::lower_bound(vnodes.begin(), vnodes.end(), hash, [](const VNode& a, const uint32_t hash) { return a.hash < hash; });
		return it->server;
	}
};

TEST(consistent_hashing, basic) {
	ConsistentHashing ch(4);
	std::map<int, int> servers;
	for (int i = 0; i < 1000; i++) {
		int server = ch.getServer(getRandomHash());
		servers[server] = servers[server] + 1;
	}
	for (auto [server, times] : servers) {
		std::cout << "Server:" << server << " " << "Times:" << times << std::endl;
	}

	// Add Server 10
	ch.addServer(10);
	std::cout << "ADD SERVER 10" << std::endl;
	servers.clear();

	for (int i = 0; i < 1000; i++) {
		int server = ch.getServer(getRandomHash());
		servers[server] = servers[server] + 1;
	}
	for (auto [server, times] : servers) {
		std::cout << "Server:" << server << " " << "Times:" << times << std::endl;
	}

	// Remove Server 2
	ch.removeServer(2);
	std::cout << "REMOVE SERVER 2" << std::endl;
	servers.clear();

	for (int i = 0; i < 1000; i++) {
		int server = ch.getServer(getRandomHash());
		servers[server] = servers[server] + 1;
	}
	for (auto [server, times] : servers) {
		std::cout << "Server:" << server << " " << "Times:" << times << std::endl;
	}
}