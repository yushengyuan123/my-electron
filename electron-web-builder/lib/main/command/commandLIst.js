"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.builderCommandLists = void 0;
const commandTypes_1 = require("./commandTypes");
const actions_1 = require("./actions");
exports.builderCommandLists = [
    {
        command: commandTypes_1.commandSorts.AddTask,
        action: actions_1.addBuilderTask
    }
];
//# sourceMappingURL=commandLIst.js.map