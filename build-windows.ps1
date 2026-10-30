param(
    [string]$CompilerBin = '',
    [string]$CMakePath = '',
    [ValidateRange(1,32)][int]$Jobs = 4
)
$ErrorActionPreference = 'Stop'
Set-Location -LiteralPath $PSScriptRoot
if (!$CompilerBin) {
    $compiler = Get-Command g++.exe -ErrorAction SilentlyContinue
    if ($compiler) { $CompilerBin = Split-Path -Parent $compiler.Source }
    elseif (Test-Path -LiteralPath 'C:\MinGW64\bin\g++.exe') { $CompilerBin = 'C:\MinGW64\bin' }
    else { throw 'Install MinGW-w64/GCC with C++17, or supply -CompilerBin.' }
}
$CompilerBin = (Resolve-Path -LiteralPath $CompilerBin).Path
$make = Join-Path $CompilerBin 'mingw32-make.exe'
if (!(Test-Path -LiteralPath $make)) { throw "Missing $make" }
$env:PATH = "$CompilerBin;$env:PATH"
if (!$CMakePath) {
    $command = Get-Command cmake.exe -ErrorAction SilentlyContinue
    if ($command) { $CMakePath = $command.Source }
    else {
        $tools = Join-Path $PSScriptRoot '.tools'
        $CMakePath = Join-Path $tools 'cmake-3.31.6-windows-x86_64\bin\cmake.exe'
        if (!(Test-Path -LiteralPath $CMakePath)) {
            New-Item -ItemType Directory -Force -Path $tools | Out-Null
            $archive = Join-Path $tools 'cmake.zip'
            [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
            Invoke-WebRequest -UseBasicParsing -Uri 'https://github.com/Kitware/CMake/releases/download/v3.31.6/cmake-3.31.6-windows-x86_64.zip' -OutFile $archive
            $expected = 'D163CD3AB4959B0A53FA8988F2DDBD2E6C501658201E6A154386BAD9DBE4F836'
            if ((Get-FileHash -LiteralPath $archive -Algorithm SHA256).Hash -ne $expected) { throw 'CMake archive checksum mismatch.' }
            Expand-Archive -LiteralPath $archive -DestinationPath $tools -Force
        }
    }
}
$CMakePath = (Resolve-Path -LiteralPath $CMakePath).Path
$ctest = Join-Path (Split-Path -Parent $CMakePath) 'ctest.exe'
& $CMakePath -S . -B build -G 'MinGW Makefiles' '-DCMAKE_BUILD_TYPE=Release' "-DCMAKE_C_COMPILER=$CompilerBin/gcc.exe" "-DCMAKE_CXX_COMPILER=$CompilerBin/g++.exe" "-DCMAKE_MAKE_PROGRAM=$make"
if ($LASTEXITCODE -ne 0) { throw 'CMake configure failed.' }
& $CMakePath --build build --parallel $Jobs
if ($LASTEXITCODE -ne 0) { throw 'Build failed.' }
& $ctest --test-dir build --output-on-failure
if ($LASTEXITCODE -ne 0) { throw 'Tests failed.' }
& $CMakePath --install build --prefix (Join-Path $PSScriptRoot 'dist') --component Game
if ($LASTEXITCODE -ne 0) { throw 'Packaging failed.' }
Write-Host "Ready: $(Join-Path $PSScriptRoot 'dist\N13Poker.exe')"
