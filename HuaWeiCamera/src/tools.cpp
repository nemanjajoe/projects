

void AnalysisMetaDataCommon(PU_META_DATA* pstMetaTargetDataCommon)
{
	PU_UserData* pstMetaUserDataCommon = pstMetaTargetDataCommon->pstMetaUserData;
	if (NULL == pstMetaUserDataCommon)
	{
		return;
	}

	for (int uIndex = 0; uIndex < pstMetaTargetDataCommon->usValidNumber; uIndex++)//common
	{
		switch (pstMetaUserDataCommon[uIndex].eType)
		{
		case CHANNEL_ID://���ͨ����
		{
			channelId = pstMetaUserDataCommon[uIndex].unMetaData.IntValue;
		}
		break;
		case IMG_WIDTH://����ͼƬ��
		{
			imgWidth = (double)pstMetaUserDataCommon[uIndex].unMetaData.IntValue;
			//picWith = imgWidth/10000.0;
		}
		break;
		case IMG_HEIGHT://����ͼƬ��
		{
			imgHeight = (double)pstMetaUserDataCommon[uIndex].unMetaData.IntValue;
			//picHeight = imgHeight/10000.0;
		}
		break;
		default:
			break;
		}
	}
}
void AnalysisMetaDataTarget(PU_META_DATA* pstMetaTargetData)
{
	PU_UserData* pstMetaUserData = pstMetaTargetData->pstMetaUserData;
	if (NULL == pstMetaUserData)
	{
		return;
	}

	for (int uIndex = 0; uIndex < pstMetaTargetData->usValidNumber; uIndex++)
	{
		switch (pstMetaUserData[uIndex].eType)
		{
		case OBJ_ID://Ŀ��ID
		{
			objId = pstMetaUserData[uIndex].unMetaData.IntValue;
		}
		break;
		case OBJ_STATUS://Ŀ��״̬
		{
			objStatus = pstMetaUserData[uIndex].unMetaData.IntValue;
		}
		break;
		case OBJ_POS://Ŀ��λ��
		{
			cout << m_Lguage["OBJ_POS"].data() << pstMetaUserData[uIndex].unMetaData.stRec.usX << "," << pstMetaUserData[uIndex].unMetaData.stRec.usY << ")" << m_Lguage["OBJ_WIDTH"].data() << pstMetaUserData[uIndex].unMetaData.stRec.usWidth << m_Lguage["OBJ_HEIGHT"].data() << pstMetaUserData[uIndex].unMetaData.stRec.usHeight << endl;
		}
		break;
		case OBJ_POS_R://Ŀ��λ��(���λ��)
		{
			cout << m_Lguage["OBJ_POS_R"].data() << pstMetaUserData[uIndex].unMetaData.stRec.usX * (double)(imgWidth / 10000.0) << "," << pstMetaUserData[uIndex].unMetaData.stRec.usY * (double)(imgHeight / 10000.0) << ")" << m_Lguage["OBJ_WIDTH"].data() << pstMetaUserData[uIndex].unMetaData.stRec.usWidth * (double)(imgWidth / 10000.0) << m_Lguage["OBJ_HEIGHT"].data() << pstMetaUserData[uIndex].unMetaData.stRec.usHeight * (double)(imgHeight / 10000.0) << endl;
		}
		break;
		case OBJ_TYPE://Ŀ������
		{
			objType = pstMetaUserData[uIndex].unMetaData.IntValue;
		}
		break;
		case OBJ_SPEED://Ŀ���ٶ�
		{
			cout << m_Lguage["OBJ_SPEED"].data() << pstMetaUserData[uIndex].unMetaData.stPoint.usX << "," << pstMetaUserData[uIndex].unMetaData.stPoint.usY << ")" << endl;
		}
		break;
		case OBJ_SPEED_R://Ŀ���ٶ�(���λ��)
		{
			cout << m_Lguage["OBJ_SPEED_R"].data() << pstMetaUserData[uIndex].unMetaData.stPoint.usX * (double)(imgWidth / 10000.0) << "," << pstMetaUserData[uIndex].unMetaData.stPoint.usY * (double)(imgHeight / 10000.0) << ")" << endl;
		}
		break;
		case TRACK_OBJECT://����Ŀ��id
		{
			printf("%s%d\r\n", m_Lguage["TRACK_OBJECT"].data(), pstMetaUserData[uIndex].unMetaData.IntValue);
		}
		break;
		case TARGET_TYPE://target����
		{
			targetType = pstMetaUserData[uIndex].unMetaData.IntValue;
			if (targetType == (int)TARGET_BEGAVIOR)
			{
				if (isStart)
				{
					cout << m_Lguage["IMG_WIDTH"].data() << imgWidth << endl;
					cout << m_Lguage["IMG_HEIGHT"].data() << imgHeight << endl;
					cout << m_Lguage["CHANNEL_ID"].data() << channelId << endl;
					isStart = false;
				}
				cout << m_Lguage["OBJ_STATUS"].data() << ConvertStatusType(objStatus).data() << endl;
				cout << m_Lguage["OBJ_TYPE"].data() << ConvertObjType(objType).data() << endl;
				cout << m_Lguage["OBJ_ID"].data() << objId << endl;
				printf("%s%s\r\n", m_Lguage["TARGET_TYPE"].data(), ConvertITGTTarget(targetType).data());
				hasTarget = true;
			}
		}
		break;
		default:
			break;
		}
	}
}
void AnalysisMetaDataRule(PU_META_DATA* pstMetaTargetDataRule)
{
	PU_UserData* pstMetaUserDataRule = pstMetaTargetDataRule->pstMetaUserData;
	if (NULL == pstMetaUserDataRule)
	{
		return;
	}
	int puanduan = 0;
	int shuju = 0;
	for (int uIndex = 0; uIndex < pstMetaTargetDataRule->usValidNumber; uIndex++)//common
	{
		switch (pstMetaUserDataRule[uIndex].eType)
		{
		case RULE_TYPE://��������
		{
			shuju = pstMetaUserDataRule[uIndex].unMetaData.IntValue;
		}
		break;
		case RULE_AREA_POS_R://�����λ��(���λ��)
		{
			if (0 == pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.uPointNum)
			{
				if (0 == puanduan)
				{
					cout << m_Lguage["RULE_AREA_POS_R_ERROR"].data() << endl;
				}
				puanduan++;
				if (4 == puanduan)
				{
					puanduan = 0;
				}
			}
			else
			{
				cout << m_Lguage["RULE_AREA_POS_R"].data() << pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.uPointNum << "   ";
				for (int i = 0; i < pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.uPointNum; i++)
				{
					cout << "(" << pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.astPts[i].usX * (double)(imgWidth / 10000.0) << "," << pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.astPts[i].usY * (double)(imgWidth / 10000.0) << ")";
				}
				cout << endl;
			}
		}
		break;
		case RULE_AREA_POS://�����λ��
		{
			if (0 == pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.uPointNum && 0 == puanduan)
			{
				if (0 == puanduan)
					cout << m_Lguage["RULE_TYPE"].data() << ConvertObjRuleType(shuju).data() << endl;
				cout << m_Lguage["RULE_AREA_POS_ERROR"].data() << endl;

			}
			else if (0 != pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.uPointNum)
			{
				cout << m_Lguage["RULE_TYPE"].data() << ConvertObjRuleType(shuju).data() << endl;
				cout << m_Lguage["RULE_AREA_POS"].data() << pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.uPointNum << "   ";
				for (int i = 0; i < pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.uPointNum; i++)
				{
					cout << "(" << pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.astPts[i].usX << "," << pstMetaUserDataRule[uIndex].unMetaData.stPolyGon.astPts[i].usY << ")";
				}
				cout << endl;
			}
		}
		break;
		default:
			break;
		}
	}
	cout << endl;
	isStart = true;
}
