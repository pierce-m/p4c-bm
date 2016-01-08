/* Copyright 2013-present Barefoot Networks, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Srikrishna Gopu (krishna@barefootnetworks.com)
 * Antonin Bas (antonin@barefootnetworks.com)
 *
 */

#include "pd/pd_pre.h"
#include "pd/pd_static.h"
#include "pd_conn_mgr.h"

extern pd_conn_mgr_t *conn_mgr_state;

extern "C" {

p4_pd_status_t p4_pd_mc_create_session(p4_pd_sess_hdl_t *sess_hdl) {
  (void) sess_hdl;
  return 0;
}

p4_pd_status_t p4_pd_mc_delete_session(p4_pd_sess_hdl_t sess_hdl) {
  (void) sess_hdl;
  return 0;
}

p4_pd_status_t p4_pd_mc_complete_operations(p4_pd_sess_hdl_t sess_hdl) {
  (void) sess_hdl;
  return 0;
}

p4_pd_status_t p4_pd_mc_mgrp_create(
  p4_pd_sess_hdl_t session, int8_t device,
  mgrp_id_t mgid, p4_pd_entry_hdl_t *mgrp_hdl
) {
  (void) session;
  *mgrp_hdl = pd_conn_mgr_mc_client(conn_mgr_state, device)->bm_mc_mgrp_create(
      0, mgid);
  return 0; // TODO
}

p4_pd_status_t p4_pd_mc_mgrp_destroy(
  p4_pd_sess_hdl_t session, int8_t device, p4_pd_entry_hdl_t mgrp_hdl
) {
  (void) session;
  pd_conn_mgr_mc_client(conn_mgr_state, device)->bm_mc_mgrp_destroy(
      0, mgrp_hdl);
  return 0; // TODO
}

namespace {

std::string convert_map(const uint8_t *input, const size_t size) {
  std::string output(size, '0');
  for(size_t i = 0; i < size; i++) {
    uint8_t byte = input[i / 8];
    int offset = i % 8;
    if(byte & (1 << offset)) {
      output[size - 1 - i] = '1';
    }
  }
  return output;
}

}

p4_pd_status_t p4_pd_mc_node_create(
  p4_pd_sess_hdl_t session, int8_t device,
  mgrp_rid_t rid, const uint8_t *port_map, const uint8_t *lag_map,
  p4_pd_entry_hdl_t *node_hdl
) {
  (void) session;
  std::string port_map_ = convert_map(port_map, PRE_PORTS_MAX);
  std::string lag_map_ = convert_map(lag_map, PRE_LAG_MAX);
  *node_hdl = pd_conn_mgr_mc_client(conn_mgr_state, device)->bm_mc_node_create(
      0, rid, port_map_, lag_map_);
  return 0; // TODO
}

p4_pd_status_t p4_pd_mc_associate_node(
  p4_pd_sess_hdl_t session, int8_t device,
  p4_pd_entry_hdl_t mgrp_hdl, p4_pd_entry_hdl_t hdl
) {
  (void) session;
  pd_conn_mgr_mc_client(conn_mgr_state, device)->bm_mc_node_associate(
      0, mgrp_hdl, hdl);
  return 0; // TODO
}

p4_pd_status_t p4_pd_mc_dissociate_node(
  p4_pd_sess_hdl_t session, int8_t device,
  p4_pd_entry_hdl_t mgrp_hdl, p4_pd_entry_hdl_t node_hdl
) {
  // TODO: needed ?
  (void) session; (void) mgrp_hdl; (void) node_hdl;
  return 0;
}

p4_pd_status_t p4_pd_mc_node_destroy(
  p4_pd_sess_hdl_t session, int8_t device, p4_pd_entry_hdl_t node_hdl
) {
  (void) session;
  pd_conn_mgr_mc_client(conn_mgr_state, device)->bm_mc_node_destroy(
      0, node_hdl);
  return 0; // TODO
}

p4_pd_status_t p4_pd_mc_node_update(
  p4_pd_sess_hdl_t session, int8_t device, p4_pd_entry_hdl_t node_hdl,
  const uint8_t *port_map, const uint8_t *lag_map
) {
  (void) session;
  std::string port_map_ = convert_map(port_map, PRE_PORTS_MAX);
  std::string lag_map_ = convert_map(lag_map, PRE_LAG_MAX);
  pd_conn_mgr_mc_client(conn_mgr_state, device)->bm_mc_node_update(
      0, node_hdl, port_map_, lag_map_);
  return 0; // TODO
}

p4_pd_status_t p4_pd_mc_set_lag_membership(
  p4_pd_sess_hdl_t session, int8_t device,
  mgrp_lag_id_t lag_id, const uint8_t *port_map
) {
  (void) session;
  std::string port_map_ = convert_map(port_map, PRE_PORTS_MAX);
  pd_conn_mgr_mc_client(conn_mgr_state, device)->bm_mc_set_lag_membership(
      0, lag_id, port_map_);
  return 0; // TODO
}

}
