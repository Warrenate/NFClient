using UnityEngine;
using System.Collections;

namespace NFSDK
{
	public abstract class NFIModule
	{
		//------------- �ӿ� -------------------//
		public abstract void Awake();
		public abstract void Init();
		public abstract void AfterInit();
		public abstract void Execute();
		public abstract void BeforeShut();
		public abstract void Shut();

		public T FindModule<T>() where T : NFIModule
		{
			return mPluginManager._FindModule<T>();
		}

		public NFIModule FindModule(string strModuleName)
		{
			return mPluginManager._FindModule(strModuleName);
		}

		public void RemoveModule<T>() where T : NFIModule
		{
			mPluginManager._RemoveModule<T>();
		}

        public NFIPluginManager mPluginManager;
        public string mName;
    };
}