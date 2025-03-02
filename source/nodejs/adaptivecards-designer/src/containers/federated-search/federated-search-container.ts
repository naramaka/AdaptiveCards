// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
import * as Adaptive from "adaptivecards";
import { HostContainer } from "../host-container";
import * as hostConfig from "../../hostConfigs/federated-search.json";

export class FederatedSearchContainer extends HostContainer {
  constructor(name: string, styleSheet: string) {
    super(name, styleSheet);

    this.actionsRegistry.unregister("Action.Submit");
    this.elementsRegistry.unregister("Input.Text");
    this.elementsRegistry.unregister("Input.Date");
    this.elementsRegistry.unregister("Input.Time");
    this.elementsRegistry.unregister("Input.Toggle");
    this.elementsRegistry.unregister("Input.ChoiceSet");
    this.elementsRegistry.unregister("Input.Number");    
    
  }

  public renderTo(hostElement: HTMLElement) {
    hostElement.classList.add("fedsearch-card");
    hostElement.appendChild(this.cardHost);
  }

  public initialize() {
    super.initialize();

  }

  public getHostConfig(): Adaptive.HostConfig {
    return new Adaptive.HostConfig(hostConfig);
  }

  get targetVersion(): Adaptive.Version {
    return Adaptive.Versions.v1_4;
  }
}
