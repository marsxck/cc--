class Solution {
public:
	bool IsPopOrder(vector<int> pushV, vector<int> popV) {
		if (pushV.size() == 0 || popV.size() == 0) return false;
		stack<int> sNum;
		int pushindex = 0;
		int popindex = 0;
		while (1)
		{
			sNum.push(pushV[pushindex]);
			if (sNum.top() == popV[popindex])
				break;
			else
			{
				pushindex++;
				if (pushindex >= pushV.size())
					return false;
			}

		}
		if (sNum.size() == 0)
			return false;
		while (popindex<popV.size())
		{
			if (sNum.top() == popV[popindex])
			{
				sNum.pop();
				popindex++;
			}
			else
			{
				if (pushindex<pushV.size())
					sNum.push(pushV[++pushindex]);
				else
					return false;
			}
		}
		return true;

	}
};