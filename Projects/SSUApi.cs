using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Runtime.InteropServices;

namespace SSUApi
{
    [StructLayout(LayoutKind.Sequential)]
    public struct  SSUDevInfo
    {
         public UInt32   version;      // main(31~24) + sub(23~16) + build(15~0)
         public UInt32   devSN;        // yy(31~24) + mm(23~20) + sn(19~0)
         [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
         public byte[] devModel;    //ascii string ended by '\0'

         public SSUDevInfo(Int32 unuse)
         {
               version = 0;
               devSN = 0;
               devModel = new byte[16];
         }
    };

    class DeskFunc
    {
        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void  SSUSetup();

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void  SSUShutup();

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        //pwd为4字节，curstomNo没有特殊说明为0
        public static extern UInt32 SSUConnect(String addr, Int32 addrType, Int32 timeout, byte[] pwd, UInt32 customNo, ref SSUDevInfo devInfo);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUTagQuery(UInt32 ctx, ref IntPtr tag, ref sbyte antNo);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        //pwd为4字节
        public static extern Int32 SSUTagRead(UInt32 ctx, byte[] pwd, byte[] tag, ref Int32 tagByts, Int32 bank, Int32 offset, Int32 words, byte[] data, sbyte antNo);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        //pwd为4字节
        public static extern Int32 SSUTagWrite(UInt32 ctx, byte[] pwd, byte[] tag, ref Int32 tagByts, Int32 bank, Int32 offset, Int32 words, byte[] data, sbyte antNo);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        //pwd为4字节，lckData为3字节
        public static extern Int32 SSUTagLock(UInt32 ctx, byte[] pwd, byte[]  tag, Int32 tagByts, byte[]  lckData, sbyte antNo);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        // oldPwd 和 newPwd均为4字节长度
        public static extern Int32 SSUConnPwdSet(UInt32 ctx, byte[] oldPwd, byte[] newPwd);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUDisconnect(UInt32 ctx, UInt32 force);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUTagReadTID(UInt32 ctx, byte[] tag, ref Int32 tagByts, Int32 offset, Int32 words, byte[] data);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUTagReadUSR(UInt32 ctx, byte[] tag, ref Int32 tagByts, Int32 offset, Int32 words, byte[] data);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUTagWriteUSR(UInt32 ctx, String tagPwd, byte[] tag, ref Int32 tagByts, Int32 offset, Int32 words, byte[] data);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUTagResetEPC(UInt32 ctx, String tagPwd, byte[] tag, Int32 tagByts, byte[] epc, Int32 epcByts);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUTagResetPWD(UInt32 ctx, String tagPwd, byte[] tag, Int32 tagByts, String accPwd, String killPwd);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUTagSolitifyEPC(UInt32 ctx, String tagPwd, byte[] tag, Int32 tagByts);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern Int32 SSUTagSolitifyUSR(UInt32 ctx, String tagPwd, byte[] tag, Int32 tagByts);

        [DllImport("SSUApiDesk.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        // passwdBuf为4字节长度
        public static extern Int32 SSUConvPwd(String passwdStr, byte[] passwdBuf);

    }
}
