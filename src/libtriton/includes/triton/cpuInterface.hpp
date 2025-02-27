//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the Apache License 2.0.
*/

#ifndef TRITON_CPUINTERFACE_HPP
#define TRITON_CPUINTERFACE_HPP

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <triton/archEnums.hpp>
#include <triton/dllexport.hpp>
#include <triton/instruction.hpp>
#include <triton/memoryAccess.hpp>
#include <triton/register.hpp>
#include <triton/tritonTypes.hpp>



//! The Triton namespace
namespace triton {
/*!
 *  \addtogroup triton
 *  @{
 */

  //! The Architecture namespace
  namespace arch {
  /*!
   *  \ingroup triton
   *  \addtogroup arch
   *  @{
   */

    /*! \interface CpuInterface
        \brief This interface is used as abstract CPU interface. All CPU must use this interface. */
    class CpuInterface {
      public:
        //! Destructor.
        TRITON_EXPORT virtual ~CpuInterface(){};

        //! Clears the architecture states (registers and memory).
        TRITON_EXPORT virtual void clear(void) = 0;

        //! Returns the kind of endianness as triton::arch::endianness_e.
        TRITON_EXPORT virtual triton::arch::endianness_e getEndianness(void) const = 0;

        //! Returns true if the register ID is a flag.
        TRITON_EXPORT virtual bool isFlag(triton::arch::register_e regId) const = 0;

        //! Returns true if the register ID is a register.
        TRITON_EXPORT virtual bool isRegister(triton::arch::register_e regId) const = 0;

        //! Returns true if the register ID is valid.
        TRITON_EXPORT virtual bool isRegisterValid(triton::arch::register_e regId) const = 0;

        //! Returns true if the execution mode is Thumb. Only useful for Arm32.
        TRITON_EXPORT virtual bool isThumb(void) const = 0;

        //! Sets CPU state to Thumb mode.
        TRITON_EXPORT virtual void setThumb(bool state) = 0;

        //! Returns true if the exclusive memory access flag is set. Only valid for Arm32.
        TRITON_EXPORT virtual bool isMemoryExclusiveAccess(void) const = 0;

        //! Sets exclusive memory access flag. Only valid for Arm32.
        TRITON_EXPORT virtual void setMemoryExclusiveAccess(bool state) = 0;

        //! Returns the bit in byte of the General Purpose Registers.
        TRITON_EXPORT virtual triton::uint32 gprSize(void) const = 0;

        //! Returns the bit in bit of the General Purpose Registers.
        TRITON_EXPORT virtual triton::uint32 gprBitSize(void) const = 0;

        //! Returns the number of registers according to the CPU architecture.
        TRITON_EXPORT virtual triton::uint32 numberOfRegisters(void) const = 0;

        //! Returns all parent registers.
        TRITON_EXPORT virtual std::set<const triton::arch::Register*> getParentRegisters(void) const = 0;

        //! Returns all registers.
        TRITON_EXPORT virtual const std::unordered_map<triton::arch::register_e, const triton::arch::Register>& getAllRegisters(void) const = 0;

        //! Returns parent register from a given one.
        TRITON_EXPORT virtual const triton::arch::Register& getParentRegister(const triton::arch::Register& reg) const = 0;

        //! Returns parent register from a given one.
        TRITON_EXPORT virtual const triton::arch::Register& getParentRegister(triton::arch::register_e id) const = 0;

        //! Returns register from id
        TRITON_EXPORT virtual const triton::arch::Register& getRegister(triton::arch::register_e id) const = 0;

        //! Returns register from name.
        TRITON_EXPORT virtual const triton::arch::Register& getRegister(const std::string& name) const = 0;

        //! Returns the program counter register
        TRITON_EXPORT virtual const triton::arch::Register& getProgramCounter(void) const = 0;

        //! Returns the stack pointer register
        TRITON_EXPORT virtual const triton::arch::Register& getStackPointer(void) const = 0;

        //! Disassembles the instruction according to the architecture.
        TRITON_EXPORT virtual void disassembly(triton::arch::Instruction& inst) = 0;

        //! Returns the concrete value of a memory cell.
        TRITON_EXPORT virtual triton::uint8 getConcreteMemoryValue(triton::uint64 addr,  bool execCallbacks=true) const = 0;

        //! Returns the concrete value of memory cells.
        TRITON_EXPORT virtual triton::uint512 getConcreteMemoryValue(const triton::arch::MemoryAccess& mem, bool execCallbacks=true) const = 0;

        //! Returns the concrete value of a memory area.
        TRITON_EXPORT virtual std::vector<triton::uint8> getConcreteMemoryAreaValue(triton::uint64 baseAddr, triton::usize size, bool execCallbacks=true) const = 0;

        //! Returns the concrete value of a register.
        TRITON_EXPORT virtual triton::uint512 getConcreteRegisterValue(const triton::arch::Register& reg, bool execCallbacks=true) const = 0;

        /*!
         * \brief [**architecture api**] - Sets the concrete value of a memory cell.
         *
         * \details Note that by setting a concrete value will probably imply a desynchronization
         * with the symbolic state (if it exists). You should probably use the concretize functions after this.
         */
        TRITON_EXPORT virtual void setConcreteMemoryValue(triton::uint64 addr, triton::uint8 value) = 0;

        /*!
         * \brief [**architecture api**] - Sets the concrete value of memory cells.
         *
         * \details Note that by setting a concrete value will probably imply a desynchronization
         * with the symbolic state (if it exists). You should probably use the concretize functions after this.
         */
        TRITON_EXPORT virtual void setConcreteMemoryValue(const triton::arch::MemoryAccess& mem, const triton::uint512& value) = 0;

        /*!
         * \brief [**architecture api**] - Sets the concrete value of a memory area.
         *
         * \details Note that by setting a concrete value will probably imply a desynchronization
         * with the symbolic state (if it exists). You should probably use the concretize functions after this.
         */
        TRITON_EXPORT virtual void setConcreteMemoryAreaValue(triton::uint64 baseAddr, const std::vector<triton::uint8>& values) = 0;

        /*!
         * \brief [**architecture api**] - Sets the concrete value of a memory area.
         *
         * \details Note that by setting a concrete value will probably imply a desynchronization
         * with the symbolic state (if it exists). You should probably use the concretize functions after this.
         */
        TRITON_EXPORT virtual void setConcreteMemoryAreaValue(triton::uint64 baseAddr, const void* area, triton::usize size) = 0;

        /*!
         * \brief [**architecture api**] - Sets the concrete value of a register.
         *
         * \details Note that by setting a concrete value will probably imply a desynchronization
         * with the symbolic state (if it exists). You should probably use the concretize functions after this.
         */
        TRITON_EXPORT virtual void setConcreteRegisterValue(const triton::arch::Register& reg, const triton::uint512& value) = 0;

        //! Returns true if memory cells have a defined concrete value
        TRITON_EXPORT virtual bool isConcreteMemoryValueDefined(const triton::arch::MemoryAccess& mem) const = 0;

        //! Returns true if memory cells have a defined concrete value
        TRITON_EXPORT virtual bool isConcreteMemoryValueDefined(triton::uint64 baseAddr, triton::usize size=1) const = 0;

        //! Clears concrete values assigned to the memory cells
        TRITON_EXPORT virtual void clearConcreteMemoryValue(const triton::arch::MemoryAccess& mem) = 0;

        //! Clears concrete values assigned to the memory cells
        TRITON_EXPORT virtual void clearConcreteMemoryValue(triton::uint64 baseAddr, triton::usize size=1) = 0;
    };

  /*! @} End of arch namespace */
  };
/*! @} End of triton namespace */
};

#endif /* TRITON_CPUINTERFACE_HPP */
