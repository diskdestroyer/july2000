/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief Functions for hooking code from the original executable.
 *
 * @copyright This file is part of July2000. 
 *            July2000 is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version 3
 *            of the License, or (at your own option) any later option. 
 *            July2000 is distributed in the hope that it will be useful,
 *            but WITHOUT ANY WARRANTY; without even the implied warranty
 *            of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 *            the GNU General Public License for more details. 
 *            You should have received a copy of the GNU General Public
 *            License along with July2000. If not, see
 *            <https://www.gnu.org/licenses/>
 */

/* Based on https://github.com/TheAssemblyArmada/Thyme */

#ifndef HOOK_H
#define HOOK_H

#include <cstdint>
#include <cstring>

#pragma pack(push, 1)
struct displ32_s {
        uint8_t cmd;    ///< Opcode.
        int32_t addr;   ///< 32-bit address.
};
#pragma pack(pop)

void Start_Hooking();
void Stop_Hooking();
extern void Init_Hooks();

/**
 * @brief Write a relative displacement instruction at the given address.
 * @param cmd Instruction opcode.
 * @param src Address to jump from.
 * @param dest Address to jump to.
 */
inline void Hook_Addr(uint8_t cmd, uintptr_t src, uintptr_t dest)
{
        displ32_s op;
        op.cmd = cmd;
        op.addr = dest - src - 5;

        std::memcpy(reinterpret_cast<void*>(src), &op, sizeof(displ32_s));
}

/**
 * @brief Write a relative jump instruction at the given address.
 * @param src Address to jump from.
 * @param dest Address to jump to.
 */
template<typename T>
inline void Hook_JMP(uintptr_t src, T dest)
{
        Hook_Addr(0xe9, src, reinterpret_cast<uintptr_t>(dest));
}

/**
 * @brief Make a global variable from an address.
 * @tparam T Variable type.
 * @param addr Variable address.
 * @return Reference to the variable.
 */
template<typename T>
inline T &Make_Global(uintptr_t addr)
{
        return *reinterpret_cast<T*>(addr);
}

/**
 * @brief Make a cdecl function from an address.
 * @tparam Ret Function return type.
 * @tparam Args... Function parameters.
 * @param addr Address of the function.
 * @return Callable function pointer.
 */
template<typename Ret, typename... Args>
inline Ret(__cdecl *Make_cdecl(const uintptr_t addr))(Args...)
{
        return reinterpret_cast<Ret(__cdecl*)(Args...)>(addr);
}

/**
 * @brief Make an stdcall function from an address.
 * @tparam Ret Function return type.
 * @tparam Args... Function parameters.
 * @param addr Address of the function.
 * @return Callable function pointer.
 */
template<typename Ret, typename... Args>
inline Ret(__stdcall *Make_stdcall(const uintptr_t addr))(Args...)
{
        return reinterpret_cast<Ret(__stdcall*)(Args...)>(addr);
}

/**
 * @brief Make a fastcall function from an address.
 * @tparam Ret Function return type.
 * @tparam Args... Function parameters.
 * @param addr Address of the function.
 * @return Callable function pointer.
 */
template<typename Ret, typename... Args>
inline Ret(__fastcall *Make_fastcall(const uintptr_t addr))(Args...)
{
        return reinterpret_cast<Ret(__fastcall*)(Args...)>(addr);
}

/**
 * @brief Make a thiscall function from an address.
 * @tparam Ret Function return type.
 * @tparam Args... Function parameters.
 * @param addr Address of the function.
 * @return Callable function pointer.
 */
template<typename Ret, typename This, typename... Args>
inline Ret(__thiscall *Make_thiscall(const uintptr_t addr))(Args...)
{
        return reinterpret_cast<Ret(__thiscall*)(This*, Args...)>(addr);
}

#endif // HOOK_H
