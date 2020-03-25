function Component() {
}

Component.prototype.createOperations = function () {
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation(
            "CreateShortcut",
            "@TargetDir@/LSerialTerm/LSerialTerm.exe",
            "@StartMenuDir@/LSerialTerm.lnk",
            "workingDirectory=@TargetDir@"
        );
    }
};
