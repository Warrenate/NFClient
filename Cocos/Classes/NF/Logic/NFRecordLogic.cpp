// -------------------------------------------------------------------------
//    @FileName			:    NFRecordLogic.cpp
//    @Author           :    Johance
//    @Date             :    2016-12-28
//    @Module           :    NFRecordLogic
//
// -------------------------------------------------------------------------

#include "stdafx.h"
#include "NFRecordLogic.h"
#include "NFComm/NFMessageDefine/NFMsgDefine.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"
#include "NFNetLogic.h"
#include "NFLoginLogic.h"

bool NFRecordLogic::Init()
{
	return true;
}

bool NFRecordLogic::Shut()
{
	return true;
}

bool NFRecordLogic::ReadyExecute()
{
	return true;
}

bool NFRecordLogic::Execute()
{


	return true;
}

bool NFRecordLogic::AfterInit()
{
	NFLogicBase::AfterInit();

	g_pNetLogic->AddReceiveCallBack(NFMsg::EGMI_ACK_RECORD_INT, this, &NFRecordLogic::OnRecordInt);
	g_pNetLogic->AddReceiveCallBack(NFMsg::EGMI_ACK_RECORD_FLOAT, this, &NFRecordLogic::OnRecordFloat);
	g_pNetLogic->AddReceiveCallBack(NFMsg::EGMI_ACK_RECORD_STRING, this, &NFRecordLogic::OnRecordString);
	g_pNetLogic->AddReceiveCallBack(NFMsg::EGMI_ACK_RECORD_OBJECT, this, &NFRecordLogic::OnRecordObject);
	g_pNetLogic->AddReceiveCallBack(NFMsg::EGMI_ACK_SWAP_ROW, this, &NFRecordLogic::OnSwapRow);
	g_pNetLogic->AddReceiveCallBack(NFMsg::EGMI_ACK_ADD_ROW, this, &NFRecordLogic::OnAddRow);
	g_pNetLogic->AddReceiveCallBack(NFMsg::EGMI_ACK_REMOVE_ROW, this, &NFRecordLogic::OnRemoveRow);

	g_pNetLogic->AddReceiveCallBack(NFMsg::EGMI_ACK_OBJECT_RECORD_ENTRY, this, &NFRecordLogic::OnObjectRecordEntry);

	return true;
}

//--------------------------------------------发消息-------------------------------------------------------------
//--------------------------------------------收消息-------------------------------------------------------------
void NFRecordLogic::OnRecordInt(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	NFGUID nPlayerID;
	NFMsg::ObjectRecordInt xMsg;
	if (!NFINetModule::ReceivePB(nMsgID, msg, nLen, xMsg, nPlayerID))
	{
		return;
	}

	NF_SHARE_PTR<NFIObject> object = g_pKernelModule->GetObject(NFINetModule::PBToNF(xMsg.player_id()));
	NF_SHARE_PTR<NFIRecordManager> recordMgr = object->GetRecordManager();
	 
	for(int i = 0; i < xMsg.property_list_size(); i++)
	{
		NF_SHARE_PTR<NFIRecord> record = recordMgr->GetElement(xMsg.record_name());

		const NFMsg::RecordInt &recordInt = xMsg.property_list(i);
		record->SetInt(recordInt.row(), recordInt.col(), recordInt.data());
	}
}

void NFRecordLogic::OnRecordFloat(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	NFGUID nPlayerID;
	NFMsg::ObjectRecordFloat xMsg;
	if (!NFINetModule::ReceivePB(nMsgID, msg, nLen, xMsg, nPlayerID))
	{
		return;
	}

	NF_SHARE_PTR<NFIObject> object = g_pKernelModule->GetObject(NFINetModule::PBToNF(xMsg.player_id()));
	NF_SHARE_PTR<NFIRecordManager> recordMgr = object->GetRecordManager();
	 
	for(int i = 0; i < xMsg.property_list_size(); i++)
	{
		NF_SHARE_PTR<NFIRecord> record = recordMgr->GetElement(xMsg.record_name());

		const NFMsg::RecordFloat &recordFloat = xMsg.property_list(i);
		record->SetFloat(recordFloat.row(), recordFloat.col(), recordFloat.data());
	}
}

void NFRecordLogic::OnRecordString(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	NFGUID nPlayerID;
	NFMsg::ObjectRecordString xMsg;
	if (!NFINetModule::ReceivePB(nMsgID, msg, nLen, xMsg, nPlayerID))
	{
		return;
	}

	NF_SHARE_PTR<NFIObject> object = g_pKernelModule->GetObject(NFINetModule::PBToNF(xMsg.player_id()));
	NF_SHARE_PTR<NFIRecordManager> recordMgr = object->GetRecordManager();
	 
	for(int i = 0; i < xMsg.property_list_size(); i++)
	{
		NF_SHARE_PTR<NFIRecord> record = recordMgr->GetElement(xMsg.record_name());

		const NFMsg::RecordString &recordString = xMsg.property_list(i);
		record->SetString(recordString.row(), recordString.col(), recordString.data());
	}
}

void NFRecordLogic::OnRecordObject(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	NFGUID nPlayerID;
	NFMsg::ObjectRecordObject xMsg;
	if (!NFINetModule::ReceivePB(nMsgID, msg, nLen, xMsg, nPlayerID))
	{
		return;
	}

	NF_SHARE_PTR<NFIObject> object = g_pKernelModule->GetObject(NFINetModule::PBToNF(xMsg.player_id()));
	NF_SHARE_PTR<NFIRecordManager> recordMgr = object->GetRecordManager();
	 
	for(int i = 0; i < xMsg.property_list_size(); i++)
	{
		NF_SHARE_PTR<NFIRecord> record = recordMgr->GetElement(xMsg.record_name());

		const NFMsg::RecordObject &recordObject = xMsg.property_list(i);
		record->SetObject(recordObject.row(), recordObject.col(), NFINetModule::PBToNF(recordObject.data()));
	}
}

void NFRecordLogic::OnSwapRow(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	NFGUID nPlayerID;
	NFMsg::ObjectRecordSwap xMsg;
	if (!NFINetModule::ReceivePB(nMsgID, msg, nLen, xMsg, nPlayerID))
	{
		return;
	}

	NF_SHARE_PTR<NFIObject> object = g_pKernelModule->GetObject(NFINetModule::PBToNF(xMsg.player_id()));
	NF_SHARE_PTR<NFIRecordManager> recordMgr = object->GetRecordManager();
	 
	NF_SHARE_PTR<NFIRecord> record = recordMgr->GetElement(xMsg.origin_record_name());
	record->SwapRowInfo(xMsg.row_origin(), xMsg.row_target());
}

void NFRecordLogic::OnAddRow(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	NFGUID nPlayerID;
	NFMsg::ObjectRecordAddRow xMsg;
	if (!NFINetModule::ReceivePB(nMsgID, msg, nLen, xMsg, nPlayerID))
	{
		return;
	}
	
	NF_SHARE_PTR<NFIObject> object = g_pKernelModule->GetObject(NFINetModule::PBToNF(xMsg.player_id()));
	NF_SHARE_PTR<NFIRecordManager> recordMgr = object->GetRecordManager();

	for(int i = 0; i < xMsg.row_data_size(); i++)
	{
		AddRecord(object, xMsg.record_name(), xMsg.row_data(i));
	}
}

void NFRecordLogic::OnRemoveRow(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	NFGUID nPlayerID;
	NFMsg::ObjectRecordRemove xMsg;
	if (!NFINetModule::ReceivePB(nMsgID, msg, nLen, xMsg, nPlayerID))
	{
		return;
	}
	
	NF_SHARE_PTR<NFIObject> object = g_pKernelModule->GetObject(NFINetModule::PBToNF(xMsg.player_id()));
	NF_SHARE_PTR<NFIRecordManager> recordMgr = object->GetRecordManager();

	for(int i = 0; i < xMsg.remove_row_size(); i++)
	{
		NF_SHARE_PTR<NFIRecord> record = recordMgr->GetElement(xMsg.record_name());
		record->Remove(xMsg.remove_row(i));
	}
}

void NFRecordLogic::OnObjectRecordEntry(const NFSOCK nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{
	NFGUID nPlayerID;
	NFMsg::MultiObjectRecordList xMsg;
	if (!NFINetModule::ReceivePB(nMsgID, msg, nLen, xMsg, nPlayerID))
	{
		return;
	}

	for(int i = 0; i < xMsg.multi_player_record_size(); i++)
	{
		const NFMsg::ObjectRecordList &data = xMsg.multi_player_record(i);
		NFGUID id = NFINetModule::PBToNF(data.player_id());

		NF_SHARE_PTR<NFIObject> object = g_pKernelModule->GetObject(id);
		for(int j = 0; j < data.record_list_size(); j++)
		{
			const NFMsg::ObjectRecordBase &objectRecord = data.record_list(j);
			const std::string &strRecordName = data.record_list(j).record_name();
			for(int k = 0; k < objectRecord.row_struct_size(); k++)
			{
				AddRecord(object, strRecordName, objectRecord.row_struct(k));
			}
		}
	}
}

void NFRecordLogic::AddRecord(const NF_SHARE_PTR<NFIObject>& object, const std::string &strRecordName, const NFMsg::RecordAddRowStruct &data)
{
	NF_SHARE_PTR<NFIRecordManager> recordMgr = object->GetRecordManager();

	NF_SHARE_PTR<NFDataList> varData = NF_SHARE_PTR<NFDataList>(NF_NEW NFDataList());
	NF_SHARE_PTR<NFDataList> varInit = NF_SHARE_PTR<NFDataList>(NF_NEW NFDataList());
	NF_SHARE_PTR<NFDataList> varTag = NF_SHARE_PTR<NFDataList>(NF_NEW NFDataList());
	for(int j = 0; j < data.record_float_list_size(); j++)
	{
		varInit->AddFloat(0);
		varData->AddFloat(data.record_float_list(j).data());
	}
	for(int j = 0; j < data.record_int_list_size(); j++)
	{
		varInit->AddInt(0);
		varData->AddInt(data.record_int_list(j).data());
	}
	for(int j = 0; j < data.record_string_list_size(); j++)
	{
		varInit->AddString("");
		varData->AddString(data.record_string_list(j).data());
	}
	for(int j = 0; j < data.record_object_list_size(); j++)
	{
		varInit->AddObject(NFGUID());
		varData->AddObject(NFINetModule::PBToNF(data.record_object_list(j).data()));
	}
	for(int j = 0; j < data.record_vector2_list_size(); j++)
	{
		varInit->AddVector2(NFVector2());
		varData->AddVector2(NFINetModule::PBToNF(data.record_vector2_list(j).data()));
	}
	for(int j = 0; j < data.record_vector3_list_size(); j++)
	{
		varInit->AddVector3(NFVector3());
		varData->AddVector3(NFINetModule::PBToNF(data.record_vector3_list(j).data()));
	}

	NF_SHARE_PTR<NFIRecord> record = recordMgr->GetElement(strRecordName);
	if(record == nullptr)
	{
		record = recordMgr->AddRecord(NFGUID(), strRecordName, varInit, varTag, 255);
	}
	record->AddRow(data.row(), *varData);
}
