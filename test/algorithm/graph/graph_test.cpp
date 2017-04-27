#include "algorithm/graph/iterative_dfs.h"
#include "algorithm/graph/topological_sort.h"
#include "algorithm/graph/tarjan_scc.h"
#include "algorithm/graph/chain_decomposition.h"
#include "algorithm/graph/transitive_closure.h"
#include "algorithm/graph/floyd_warshall.h"
#include "algorithm/graph/dijkstra.h"
#include "algorithm/graph/dinic_flow.h"
#include "algorithm/graph/push_relabel_flow.h"
#include "algorithm/graph/bipartite_matching.h"
#include "algorithm/graph/lowest_common_ancestor.h"
#include "algorithm/graph/heavy_light_decomposition.h"

#include "algorithm/collections/collections.h"

#include "gtest/gtest.h"

using namespace std;
using namespace altruct::graph;
using namespace altruct::collections;

namespace {
    vector<vector<pair<int, int>>> adjl_dag_neg1{ // no cycles, has negative weights, multiple components
        { { 4, 10 } },
        { { 4, 7 }, { 0, 3 } },
        { { 0, 5 } },
        { { 2, -4 }, { 0, 6 }, { 1, 8 }, { 4, 5 } },
        {},
        { { 1, -2 }, { 6, 6 } },
        {},
        { { 6, 7 } },
        { { 10, -5 } },
        {},
        {},
    };
    vector<vector<pair<int, int>>> adjl_cyc_neg1{ // has cycles, has negative weights, but no negative cycles
        { { 2, -2 } },
        { { 0, 4 }, { 2, 3 } },
        { { 3, 2 } },
        { { 1, -1 }, { 4, -8 } },
        { { 5, 2 } },
        { { 6, 3 } },
        { { 4, 7 } },
        { { 5, 10 }, { 5, 6 }, { 5, 11 } },
    };
    vector<vector<pair<int, int>>> adjl_cyc_pos1{ // has cycles, only positive weights
        { { 2, 2 } },
        { { 0, 4 }, { 2, 3 }, { 4, 20 } },
        { { 3, 2 } },
        { { 1, 1 }, { 4, 8 } },
        { { 5, 2 } },
        { { 6, 3 } },
        { { 4, 7 } },
        { { 5, 10 }, { 5, 6 }, { 5, 11 } },
    };
    vector<vector<pair<int, int>>> adjl_cyc_undir{ // undirected, has cycles, multiple components
        { { 5, 21 }, { 7, 28 }, { 8, 23 } },
        { { 2, 31 }, { 4, 33 } },
        { { 1, 27 }, { 4, 35 } },
        { { 6, 28 }, { 9, 26 } },
        { { 1, 34 }, { 2, 28 }, { 9, 34 } },
        { { 0, 31 }, { 7, 26 }, { 9, 29 } },
        { { 3, 25 }, { 9, 28 } },
        { { 0, 32 }, { 5, 33 }, { 8, 31 }, { 9, 30 } },
        { { 0, 29 }, { 7, 35 } },
        { { 4, 26 }, { 5, 28 }, { 6, 30 }, { 7, 32 }, { 3, 24 } },
        { { 11, 45 } },
        { { 10, 38 }, { 12, 45 } },
        { { 11, 42 } },
        { { 14, 55 }, { 15, 57 } },
        { { 13, 57 }, { 15, 54 } },
        { { 13, 53 }, { 14, 52 }, { 16, 54 }, { 17, 50 } },
        { { 15, 58 }, { 17, 55 } },
        { { 15, 58 }, { 16, 56 } },
    };
    auto index_f = [](const pair<int, int>& e){return e.first; };
}

TEST(graph_test, iterative_dfs) {
    // TODO
}

TEST(graph_test, in_degrees) {
    EXPECT_EQ((vector<int>{3, 2, 1, 0, 3, 0, 2, 0, 0, 0, 1}), in_degrees(adjl_dag_neg1, index_f));
}

TEST(graph_test, topological_sort) {
    EXPECT_EQ((vector<int>{ 9, 8, 10, 7, 5, 6, 3, 1, 2, 0, 4 }), topological_sort(adjl_dag_neg1, index_f));
}

TEST(graph_test, tarjan_scc) {
    EXPECT_EQ((vector<vector<int>>{{ 9 }, { 8 }, { 10 }, { 7 }, { 5 }, { 6 }, { 3 }, { 2 }, { 1 }, { 0 }, { 4 } }), tarjan_scc(adjl_dag_neg1, index_f));
    EXPECT_EQ((vector<vector<int>>{{ 7 }, { 1, 3, 2, 0 }, { 6, 5, 4 } }), tarjan_scc(adjl_cyc_neg1, index_f));
}

TEST(graph_test, chain_decomposition) {
    const auto d = chain_decomposition(adjl_cyc_undir, index_f);
    EXPECT_EQ((vector<vector<vector<int>>>{{ { 0, 7, 5, 0 }, { 0, 8, 7 }, { 5, 9, 7 }, { 9, 3, 6, 9 }, { 4, 2, 1, 4 } }, {}, { { 13, 15, 14, 13 }, { 15, 17, 16, 15 } }}), d);
    EXPECT_EQ((vector<int>{ 4, 9, 11, 15 }), sorted(cut_vertices(adjl_cyc_undir, index_f, d)));
    EXPECT_EQ((vector<pair<int, int>>{{ 4, 9 }, { 10, 11 }, { 11, 12 } }), sorted(cut_edges(adjl_cyc_undir, index_f, d)));
    EXPECT_EQ((vector<vector<int>>{{ 0, 7, 5, 8, 9 }, { 4, 2, 1 }, { 9, 3, 6 }, { 13, 15, 14 }, { 15, 17, 16 } }), sorted(biconnected_components(adjl_cyc_undir, index_f, d)));
    auto cve = cut_vertices_and_edges(adjl_cyc_undir, index_f);
    EXPECT_EQ((vector<int>{ 4, 9, 11, 15 }), sorted(cve.first));
    EXPECT_EQ((vector<pair<int, int>>{{ 4, 9 }, { 10, 11 }, { 11, 12 } }), sorted(cve.second));
}

TEST(graph_test, transitive_closure) {
    EXPECT_EQ((vector<vector<int>>{{ 4 }, { 4, 0 }, { 0, 4 }, { 2, 0, 1, 4 }, {}, { 1, 6, 4, 0 }, {}, { 6 }, { 10 }, {}, {} }), transitive_closure(adjl_dag_neg1, index_f));
    EXPECT_EQ((vector<vector<int>>{{ 4 }, { 0 }, { 0 }, { 1, 2 }, {}, { 1, 6 }, {}, { 6 }, { 10 }, {}, {} }), transitive_reduction(adjl_dag_neg1, index_f));
    EXPECT_EQ((vector<vector<int>>{{ 4 }, { 0 }, { 0 }, { 1, 2 }, {}, { 1, 6 }, {}, { 6 }, { 10 }, {}, {} }), transitive_reduction(transitive_closure(adjl_dag_neg1, index_f)));
    EXPECT_EQ((vector<vector<int>>{{ 2, 3, 1, 4, 5, 6 }, { 0, 2, 3, 4, 5, 6 }, { 3, 1, 4, 5, 6, 0 }, { 1, 4, 5, 6, 0, 2 }, { 5, 6 }, { 6, 4 }, { 4, 5 }, { 5, 6, 4 } }), transitive_closure(adjl_cyc_neg1, index_f));
}

TEST(graph_test, floyd_warshall) {
    int INF = 1000000000;
    EXPECT_EQ((vector<vector<pair<int, int>>> {
        { { 0, 0 }, { 2, -1 }, { 2, -2 }, { 2, 0 }, { 2, -8 }, { 2, -6 }, { 2, -3 }, { -1, INF } },
        { { 0, 4 }, { 1, 0 }, { 0, 2 }, { 0, 4 }, { 0, -4 }, { 0, -2 }, { 0, 1 }, { -1, INF } },
        { { 3, 5 }, { 3, 1 }, { 2, 0 }, { 3, 2 }, { 3, -6 }, { 3, -4 }, { 3, -1 }, { -1, INF } },
        { { 1, 3 }, { 1, -1 }, { 1, 1 }, { 3, 0 }, { 4, -8 }, { 4, -6 }, { 4, -3 }, { -1, INF } },
        { { -1, INF }, { -1, INF }, { -1, INF }, { -1, INF }, { 4, 0 }, { 5, 2 }, { 5, 5 }, { -1, INF } },
        { { -1, INF }, { -1, INF }, { -1, INF }, { -1, INF }, { 6, 10 }, { 5, 0 }, { 6, 3 }, { -1, INF } },
        { { -1, INF }, { -1, INF }, { -1, INF }, { -1, INF }, { 4, 7 }, { 4, 9 }, { 6, 0 }, { -1, INF } },
        { { -1, INF }, { -1, INF }, { -1, INF }, { -1, INF }, { 5, 16 }, { 5, 6 }, { 5, 9 }, { 7, 0 } }
    }), floyd_warshall(adjl_cyc_neg1, INF));
}

TEST(graph_test, dijkstra) {
    int INF = 1000000000;
    EXPECT_EQ((vector<pair<int, int>>{{ 0, 0 }, { 3, 5 }, { 0, 2 }, { 2, 4 }, { 3, 12 }, { 4, 14 }, { 5, 17 }, { -1, INF } }), dijkstra(adjl_cyc_pos1, 0, INF));
    EXPECT_EQ((vector<pair<int, int>>{{ 1, 4 }, { 1, 0 }, { 1, 3 }, { 2, 5 }, { 3, 13 }, { 4, 15 }, { 5, 18 }, { -1, INF } }), dijkstra(adjl_cyc_pos1, 1, INF));
    EXPECT_EQ((vector<pair<int, int>>{{ 1, 7 }, { 3, 3 }, { 2, 0 }, { 2, 2 }, { 3, 10 }, { 4, 12 }, { 5, 15 }, { -1, INF } }), dijkstra(adjl_cyc_pos1, 2, INF));
    EXPECT_EQ((vector<pair<int, int>>{{ 1, 5 }, { 3, 1 }, { 1, 4 }, { 3, 0 }, { 3, 8 }, { 4, 10 }, { 5, 13 }, { -1, INF } }), dijkstra(adjl_cyc_pos1, 3, INF));
    EXPECT_EQ((vector<pair<int, int>>{{ -1, INF }, { -1, INF }, { -1, INF }, { -1, INF }, { 4, 0 }, { 4, 2 }, { 5, 5 }, { -1, INF } }), dijkstra(adjl_cyc_pos1, 4, INF));
    EXPECT_EQ((vector<pair<int, int>>{{ -1, INF }, { -1, INF }, { -1, INF }, { -1, INF }, { 6, 10 }, { 5, 0 }, { 5, 3 }, { -1, INF } }), dijkstra(adjl_cyc_pos1, 5, INF));
    EXPECT_EQ((vector<pair<int, int>>{{ -1, INF }, { -1, INF }, { -1, INF }, { -1, INF }, { 6, 7 }, { 4, 9 }, { 6, 0 }, { -1, INF } }), dijkstra(adjl_cyc_pos1, 6, INF));
    EXPECT_EQ((vector<pair<int, int>>{{ -1, INF }, { -1, INF }, { -1, INF }, { -1, INF }, { 6, 16 }, { 7, 6 }, { 5, 9 }, { 7, 0 } }), dijkstra(adjl_cyc_pos1, 7, INF));
}


template<typename MAX_FLOW_IMPL, typename T>
void test_max_flow(const vector<vector<T>>& capacities, const vector<vector<T>>& expected_flows) {
    MAX_FLOW_IMPL mfi(capacities, 1000000);
    vector<vector<T>> actual_flows = capacities;
    for (int i = 0; i < mfi.cap.size(); i++) {
        for (int j = 0; j < mfi.cap.size(); j++) {
            actual_flows[i][j] = mfi.calc_max_flow(i, j);
        }
    }
    EXPECT_EQ(expected_flows, actual_flows);
}

TEST(graph_test, dinic_flow) {
    test_max_flow<dinic_flow<int>, int>({ { 0 } }, { { 0 } });
    test_max_flow<dinic_flow<int>, int>({ { 0, 5 }, { 7, 0 } }, { { 0, 5 }, { 7, 0 } });
    test_max_flow<dinic_flow<int>, int>({ { 0, 3, 5 }, { 0, 0, 2 }, { 0, 0, 0 } }, { { 0, 3, 7 }, { 0, 0, 2 }, { 0, 0, 0 } });
    test_max_flow<dinic_flow<double>, double>({ { 0, 5, 2 }, { 7, 0, 4 }, { 1, 3, 0 } }, { { 0, 7, 6 }, { 8, 0, 6 }, { 4, 4, 0 } });
}

TEST(graph_test, push_relabel_flow) {
    test_max_flow<push_relabel_flow<int>, int>({ { 0 } }, { { 0 } });
    test_max_flow<push_relabel_flow<int>, int>({ { 0, 5 }, { 7, 0 } }, { { 0, 5 }, { 7, 0 } });
    test_max_flow<push_relabel_flow<int>, int>({ { 0, 3, 5 }, { 0, 0, 2 }, { 0, 0, 0 } }, { { 0, 3, 7 }, { 0, 0, 2 }, { 0, 0, 0 } });
    test_max_flow<push_relabel_flow<double>, double>({ { 0, 5, 2 }, { 7, 0, 4 }, { 1, 3, 0 } }, { { 0, 7, 6 }, { 8, 0, 6 }, { 4, 4, 0 } });
}

TEST(graph_test, bipartite_matching) {
    typedef std::vector<std::pair<int, int>> edges_t;
    EXPECT_EQ((edges_t()), bipartite_matching(0, edges_t()));
    EXPECT_EQ((edges_t{ { 0, 2 }, { 1, 3 } }), bipartite_matching(4, edges_t{ { 0, 2 }, { 0, 3 }, { 1, 3 } }));
    EXPECT_EQ((edges_t{ { 0, 2 }, { 1, 3 } }), bipartite_matching(4, edges_t{ { 0, 2 }, { 1, 2 }, { 1, 3 } }));
}

TEST(graph_test, lowest_common_ancestor) {
	vector<vector<int>> adjl{ { 1, 2 }, { 0 }, { 0, 3 }, { 2 } };
	lowest_common_ancestor lca(adjl);
	EXPECT_EQ(0, lca.ancestor(1, 3));
}

TEST(graph_test, heavy_light_decomposition) {
	vector<vector<int>> adjl{ { 1, 2 }, { 0 }, { 0, 3 }, { 2 } };
	heavy_light_decomposition_ex hld(adjl);
	EXPECT_EQ(3, hld.parent(3, 0));
	EXPECT_EQ(2, hld.parent(3, 1));
	EXPECT_EQ(0, hld.parent(3, 2));
}
