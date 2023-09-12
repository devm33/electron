// Copyright (c) 2022 Microsoft, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ELECTRON_SHELL_SERVICES_NODE_NODE_SERVICE_H_
#define ELECTRON_SHELL_SERVICES_NODE_NODE_SERVICE_H_

#include <memory>

#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "services/network/public/mojom/url_loader_factory.mojom.h"
#include "shell/services/node/public/mojom/node_service.mojom.h"

namespace node {

class Environment;

}  // namespace node

namespace electron {

class ElectronBindings;
class JavascriptEnvironment;
class NodeBindings;

class NodeService : public node::mojom::NodeService {
 public:
  explicit NodeService(
      mojo::PendingReceiver<node::mojom::NodeService> receiver);
  ~NodeService() override;

  NodeService(const NodeService&) = delete;
  NodeService& operator=(const NodeService&) = delete;

  // mojom::NodeService implementation:
  void Initialize(node::mojom::NodeServiceParamsPtr params) override;
  void SetURLLoaderFactory(
      ::mojo::PendingRemote<::network::mojom::URLLoaderFactory>
          url_loader_factory) override;

 private:
  bool node_env_stopped_ = false;
  std::unique_ptr<JavascriptEnvironment> js_env_;
  std::unique_ptr<NodeBindings> node_bindings_;
  std::unique_ptr<ElectronBindings> electron_bindings_;
  std::shared_ptr<node::Environment> node_env_;
  mojo::Receiver<node::mojom::NodeService> receiver_{this};
};

}  // namespace electron

#endif  // ELECTRON_SHELL_SERVICES_NODE_NODE_SERVICE_H_
