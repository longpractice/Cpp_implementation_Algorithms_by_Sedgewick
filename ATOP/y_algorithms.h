#pragma once

/********Accumuate********/

//first version
template<typename TInputIterator, typename T>
T accumulate(TInputIterator begin, TInputIterator end, T init)
{
	for (; begin != end; ++begin)
		init = init + *begin;
	return init;
}

//second version
template<typename TInputIterator, typename T, typename BinaryOp>
T accumulate(TInputIterator begin, TInputIterator end, T init, BinaryOp binary_op)
{
	for (; begin != end; ++begin)
		init = binary_op(init, begin);
	return init;
}


/*******Adjacent_difference******/
template<typename TInputIterator, typename TOutputIterator>
TOutputIterator adjacent_difference(TInputIterator begin, TInputIterator end, TOutputIterator result)
{
	if (begin == end) return result;
	*result = *begin;
	auto val = *begin;
	while (++begin != end)
	{
		auto tmp = *begin;
		*++result = tmp - val;
		val = tmp;
	}
	return ++result;
}

template<typename TInputIterator, typename TOutputIterator, typename Binary_op>
TOutputIterator adjacent_difference(TInputIterator begin, TInputIterator end, TOutputIterator result, Binary_op binary_op)
{
	if (begin == end) return result;
	*result = *begin;
	auto val = *begin;
	while (++begin != end)
	{
		auto tmp = *begin;
		*++result = binary_op(tmp, val);
		val = tmp;
	}
	return ++result;
}

/********Inner product******/
template<typename TInputIterator1, typename TInputIterator2, typename T>
T inner_product(TInputIterator1 begin1, TInputIterator1 end1, TInputIterator2 begin2, T init)
{
	for (; begin1 != end1; ++begin1, ++)
		init = init + (*begin1)*(*begin2);
	return init;
}

template<typename TInputIterator1, typename TInputIterator2, typename T, typename Binary_op1, typename Binary_op2>
T inner_product(TInputIterator1 begin1, TInputIterator1 end1, TInputIterator2 begin2, T init, Binary_op1 binary_op1, Binary_op2 binary_op2)
{
	for (; begin1 != end1; ++begin1, ++)
		init = binary_op1(init, binary_op2(*begin1, *begin2));
	return init;
}

/*******Partial Sum********/
template<typename TInputIterator, typename TOutputIterator>
TOutputIterator patial_sum(TInputIterator begin, TInputIterator end, TOutputIterator result)