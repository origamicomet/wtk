-- =============================================================================
-- This file is part of the Windowing Toolkit.
-- Copyright (C) 2012 Michael Williams <devbug@bitbyte.ca>
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.
-- =============================================================================

if _ACTION and _ACTION ~= "help" then

solution "wtk"
    location("build/" .. _ACTION)
    configurations({ "debug", "release" })

    project("sample")
        kind("WindowedApp")
        language("C")
        objdir("build/" .. _ACTION .. "/sample/obj" )
        targetdir("bin/" .. _ACTION .. "/")
        targetname("sample")
        debugdir("sample")

        configuration("debug") targetsuffix("-dbg") flags({ "Symbols" }) links("libwtk")
        configuration("release") flags({ "Optimize", "EnableSSE", "EnableSSE2" }) links("libwtk")

        configuration({})
            libdirs({ "lib/" .. _ACTION })
            defines({ "WTK_DLL" })
            includedirs({ "include" })
            files { "sample/**.c" }

    project("libwtk")
        kind("SharedLib")
        language("C")
        objdir("build/" .. _ACTION .. "/libwtk/obj" )
        targetdir("lib/" .. _ACTION .. "/")
        targetname("wtk")

        configuration("debug") targetsuffix("-dbg") flags({ "Symbols" })
        configuration("release") flags({ "Optimize", "EnableSSE", "EnableSSE2" })

        configuration({})
            defines({ "WTK_DLL", "WTK_BUILD" })
            includedirs { "include" }
            files { "include/**.h", "include/**.inl", "source/**.c" }

        configuration("windows")
            links({ "comctl32" })
            defines({ "ISOLATION_AWARE_ENABLED=1" })
            postbuildcommands({ "move \"..\\..\\lib\\" .. _ACTION .. "\\*.dll\" \"..\\..\\bin\\" .. _ACTION .. "\\\"" })
end
