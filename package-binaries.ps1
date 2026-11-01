# --- CONFIGURATION ---
$ProjectName = "SpaceTruckers"
$RootDir     = "G:\projects\space-truckers"
$DistDir     = "G:\projects\space-truckers-distribution"
$ZipPath     = "G:\projects\space-truckers-distribution.zip"
$RunUATPath  = "G:\Epic Games\UE_5.8\Engine\Build\BatchFiles\RunUAT.bat"

Clear-Host
Write-Host "=========================================================="
Write-Host "STARTING FULL PRECOMPILED CORE BUILD & PACKAGE PIPELINE"
Write-Host "=========================================================="

# --- STEP 1: VALIDATION ---
if (!(Test-Path $RunUATPath)) {
    Write-Error "Error: Could not find Unreal Automation Tool at: $RunUATPath. Please check your Engine path configuration."
    Exit
}

if (!(Test-Path "$RootDir\$ProjectName.uproject")) {
    Write-Error "Error: Could not find your project file at: $RootDir\$ProjectName.uproject"
    Exit
}

# --- STEP 2: COMPILE STANDALONE RUNTIME & EDITOR TARGETS ---
Write-Host "`nStep 1/4: Compiling Standalone Runtime and Editor targets..."

# Execute full compilation pass via UAT to generate Editor binaries (.dll) and standalone engine makefiles
& $RunUATPath BuildCookRun `
    -project="$RootDir\$ProjectName.uproject" `
    -targetplatform=Win64 `
    -config=Development `
    -build `
    -skipcook `
    -stage

if ($LASTEXITCODE -ne 0) {
    Write-Error "Error: Unreal Build step failed! Directives or syntax bugs remain in your C++ modules."
    Exit
}
Write-Host "Compilation successful!"

# --- STEP 3: ENVIRONMENT CLEANUP & PREPARATION ---
Write-Host "`nStep 2/4: Cleaning up old paths and preparing staging directories..."
if (Test-Path $DistDir) { 
    Remove-Item -Path $DistDir -Recurse -Force 
}
if (Test-Path $ZipPath) {
    Remove-Item -Path $ZipPath -Force
}
New-Item -ItemType Directory -Path $DistDir | Out-Null

# --- STEP 4: PACKAGING & STRIPPING PRIVACY CODE ---
Write-Host "`nStep 3/4: Copying binaries and stripping source (.cpp) files..."

# 1. Copy project base configuration files and built binaries
Copy-Item "$RootDir\$ProjectName.uproject" $DistDir
Copy-Item "$RootDir\Config" $DistDir -Recurse -Force
Copy-Item "$RootDir\Content" $DistDir -Recurse -Force
Copy-Item "$RootDir\Binaries" $DistDir -Recurse -Force

# 2. Create the stripped Source folder layout (Public Headers Only)
$PublicSourceSrc = "$RootDir\Source\$ProjectName"
$PublicSourceDst = "$DistDir\Source\$ProjectName"
New-Item -ItemType Directory -Path $PublicSourceDst | Out-Null

# Copy base target build configurations and interface headers
Copy-Item "$PublicSourceSrc\$ProjectName.Build.cs" $PublicSourceDst
Copy-Item "$PublicSourceSrc\$ProjectName.h" $PublicSourceDst
Copy-Item "$PublicSourceSrc\$ProjectName.cpp" $PublicSourceDst

# Safely copy only public headers so other teams can inherit your framework classes
if (Test-Path "$PublicSourceSrc\Public") {
    Copy-Item "$PublicSourceSrc\Public" $PublicSourceDst -Recurse -Force
}

# 3. Extract and isolate linker files from Intermediate for other team compilers
$IntBaseSrc = "$RootDir\Intermediate\Build\Win64"
$IntDst     = "$DistDir\Intermediate\Build\Win64\UnrealEditor\Development\$ProjectName"
New-Item -ItemType Directory -Path $IntDst -Force | Out-Null

if (Test-Path $IntBaseSrc) {
    # Scan the local intermediate directory to isolate linker metrics (.lib, .modules, generated reflections)
    Get-ChildItem -Path $IntBaseSrc -Include "*.lib", "*.modules", "*.generated.h" -Recurse | ForEach-Object {
        $FileName = $_.Name
        # Flatten compiler assets directly into the distribution directory for the team compiler
        Copy-Item $_.FullName (Join-Path $IntDst $FileName) -Force
    }
}

# --- STEP 5: ZIP COMPRESSION ---
Write-Host "`nStep 4/4: Compiling package into a single zip archive..."
Compress-Archive -Path "$DistDir\*" -DestinationPath $ZipPath -Force

Write-Host "`n=========================================================="
Write-Host "SUCCESS: Precompiled framework packaged and compressed!"
Write-Host "Folder Location: $DistDir"
Write-Host "Zip Archive Location: $ZipPath"
Write-Host "=========================================================="
